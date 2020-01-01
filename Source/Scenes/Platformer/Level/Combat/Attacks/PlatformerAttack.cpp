#include "PlatformerAttack.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Projectiles/Projectile.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const float PlatformerAttack::DefaultCleanupDuration = 5.0f;

PlatformerAttack::PlatformerAttack(AttackType attackType, std::string iconResource, float probabilityWeight, int baseDamageOrHealingMin, int baseDamageOrHealingMax, int specialCost, float attackDuration, float recoverDuration, float cleanupDuration)
{
	this->attackType = attackType;
	this->iconResource = iconResource;
	this->probabilityWeight = probabilityWeight;
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
		for (auto it = this->attackCompleteCallbacks.begin(); it != attackCompleteCallbacks.end(); it++)
		{
			attack->registerAttackCompleteCallback(*it);
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

float PlatformerAttack::getProbabilityWeight()
{
	return this->probabilityWeight;
}

int PlatformerAttack::getSpecialCost()
{
	return this->specialCost;
}

PlatformerAttack::AttackType PlatformerAttack::getAttackType()
{
	return this->attackType;
}

void PlatformerAttack::execute(PlatformerEntity* owner, PlatformerEntity* target, std::function<void()> onAttackComplete)
{
	this->onAttackTelegraphBegin();

	int mana = std::max(0, owner->getStateOrDefaultInt(StateKeys::Mana, 0) - this->getSpecialCost());
	owner->setState(StateKeys::Mana, Value(mana));

	this->runAction(Sequence::create(
		DelayTime::create(this->getAttackDuration()),
		CallFunc::create([=]()
		{
			this->performAttack(owner, target);
		}),
		DelayTime::create(this->getRecoverDuration()),
		CallFunc::create([=]()
		{
			onAttackComplete();

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
		ObjectEvents::PositionMode::Discard
	));

	Node* reference = weapon == nullptr ? (Node*)owner : (Node*)weapon;

	projectile->setPosition3D(GameUtils::getWorldCoords3D(reference));

	// We dont actually want to set the Z to the world coord Z position, as this would end up re-applying any layer depth
	projectile->setPositionZ(reference->getPositionZ());
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
