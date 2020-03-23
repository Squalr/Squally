#include "PlatformerAttack.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Projectiles/Projectile.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const float PlatformerAttack::DefaultCleanupDuration = 5.0f;
const float PlatformerAttack::PriorityCommon = 0.5f;
const float PlatformerAttack::PriorityUncommon = 0.2f;
const float PlatformerAttack::PriorityRare = 0.1f;

PlatformerAttack::PlatformerAttack(AttackType attackType, std::string iconResource, float priority, int baseDamageOrHealingMin, int baseDamageOrHealingMax, int specialCost, float attackDuration, float recoverDuration, float cleanupDuration)
{
	this->attackType = attackType;
	this->iconResource = iconResource;
	this->priority = priority;
	this->baseDamageOrHealingMin = std::abs(std::min(baseDamageOrHealingMin, baseDamageOrHealingMax));
	this->baseDamageOrHealingMax = std::abs(std::max(baseDamageOrHealingMin, baseDamageOrHealingMax));
	this->specialCost = specialCost;
	this->attackDuration = attackDuration;
	this->recoverDuration = recoverDuration;
	this->attackCompleteCallbacks = std::vector<std::function<void()>>();
}

PlatformerAttack* PlatformerAttack::clone()
{
	PlatformerAttack* attack = this->cloneInternal();

	if (attack != nullptr)
	{
		for (auto next : this->attackCompleteCallbacks)
		{
			attack->registerAttackCompleteCallback(next);
		}
	}

	return attack;
}

void PlatformerAttack::registerAttackCompleteCallback(std::function<void()> callback)
{
	this->attackCompleteCallbacks.push_back(callback);
}

std::string PlatformerAttack::getAttackAnimation()
{
	return "Attack";
}

std::string PlatformerAttack::getIconResource()
{
	return this->iconResource;
}

float PlatformerAttack::getPriority()
{
	return this->priority;
}

int PlatformerAttack::getSpecialCost()
{
	return this->specialCost;
}

PlatformerAttack::AttackType PlatformerAttack::getAttackType()
{
	return this->attackType;
}

void PlatformerAttack::execute(PlatformerEntity* owner, PlatformerEntity* target, std::function<void()> onCastComplete, std::function<void()> onRecoverComplete)
{
	this->onAttackTelegraphBegin();

	owner->getAttachedBehavior<EntityManaBehavior>([=](EntityManaBehavior* manaBehavior)
	{
		manaBehavior->setMana(manaBehavior->getMana() - this->getSpecialCost());
	});

	this->runAction(Sequence::create(
		DelayTime::create(this->getAttackDuration()),
		CallFunc::create([=]()
		{
			onCastComplete();
			
			// Damage/healing is applied at this stage. For projectiles, they are spawned here.
			this->performAttack(owner, target);
		}),
		// The recover duration gives the camera time to focus the entity that took damage, and for projectiles to run their course.
		DelayTime::create(this->getRecoverDuration()),
		CallFunc::create([=]()
		{
			onRecoverComplete();

			this->onAttackEnd();
		}),
		nullptr
	));
}

void PlatformerAttack::onAttackTelegraphBegin()
{
}

void PlatformerAttack::doDamageOrHealing(PlatformerEntity* owner, PlatformerEntity* target)
{
}

void PlatformerAttack::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
}

bool PlatformerAttack::isWorthUsing(const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	return true;
}

void PlatformerAttack::onAttackEnd()
{
	for (auto it = this->attackCompleteCallbacks.begin(); it != this->attackCompleteCallbacks.end(); it++)
	{
		(*it)();
	}
}

void PlatformerAttack::onCleanup()
{
}

std::string PlatformerAttack::getMainhandResource(PlatformerEntity* owner)
{
	AnimationPart* weapon = owner->getAnimations()->getAnimationPart("mainhand");

	if (weapon != nullptr)
	{
		return weapon->getSpriteResource();
	}

	return "";
}

std::string PlatformerAttack::getOffhandResource(PlatformerEntity* owner)
{
	AnimationPart* weapon = owner->getAnimations()->getAnimationPart("offhand");

	if (weapon != nullptr)
	{
		return weapon->getSpriteResource();
	}

	return "";
}

void PlatformerAttack::replaceMainhandWithProjectile(PlatformerEntity* owner, Projectile* projectile)
{
	this->replaceAnimationPartWithProjectile("mainhand", owner, projectile);
}

void PlatformerAttack::replaceOffhandWithProjectile(PlatformerEntity* owner, Projectile* projectile)
{
	this->replaceAnimationPartWithProjectile("offhand", owner, projectile);
}

void PlatformerAttack::replaceAnimationPartWithProjectile(std::string animationPart, PlatformerEntity* owner, Projectile* projectile)
{
	AnimationPart* weapon = owner->getAnimations()->getAnimationPart(animationPart);

	if (weapon != nullptr)
	{
		weapon->replaceWithObject(projectile, 2.0f);
	}

	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
		owner,
		projectile,
		ObjectEvents::SpawnMethod::Above,
		ObjectEvents::PositionMode::Discard,
		[&]()
		{
		},
		[&]()
		{
		}
	));

	Node* reference = weapon == nullptr ? (Node*)owner : (Node*)weapon;
	float layerZ = GameUtils::getDepth(GameUtils::getFirstParentOfType<MapLayer>(reference));

	// Set the position to the reference object's position. Offset it by any layer positioning.
	projectile->setPosition3D(GameUtils::getWorldCoords3D(reference) - Vec3(0.0f, 0.0f, layerZ));
}

int PlatformerAttack::getRandomDamage()
{
	return -RandomHelper::random_int(this->getBaseDamageMin(), this->getBaseDamageMax());
}

int PlatformerAttack::getBaseDamageMin()
{
	return this->baseDamageOrHealingMin;
}

int PlatformerAttack::getBaseDamageMax()
{
	return this->baseDamageOrHealingMax;
}

int PlatformerAttack::getRandomHealing()
{
	return RandomHelper::random_int(this->getBaseDamageMin(), this->getBaseDamageMax());
}

int PlatformerAttack::getBaseHealingMin()
{
	return this->baseDamageOrHealingMin;
}

int PlatformerAttack::getBaseHealingMax()
{
	return this->baseDamageOrHealingMax;
}

float PlatformerAttack::getAttackDuration()
{
	return this->attackDuration;
}

float PlatformerAttack::getRecoverDuration()
{
	return this->recoverDuration;
}
