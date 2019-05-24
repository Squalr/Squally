#include "PlatformerAttack.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Projectile.h"

using namespace cocos2d;

const float PlatformerAttack::DefaultCleanupDuration = 5.0f;

PlatformerAttack::PlatformerAttack(AttackType attackType, std::string iconResource, float priority, int baseDamageOrHealingMin, int baseDamageOrHealingMax, int specialCost, float attackDuration, float recoverDuration, float cleanupDuration)
{
	this->attackType = attackType;
	this->iconResource = iconResource;
	this->priority = priority;
	this->baseDamageOrHealingMin = baseDamageOrHealingMin;
	this->baseDamageOrHealingMax = baseDamageOrHealingMax;
	this->specialCost = specialCost;
	this->attackDuration = attackDuration;
	this->recoverDuration = recoverDuration;
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

void PlatformerAttack::execute(PlatformerEntity* owner, PlatformerEntity* target, std::function<void()> onAttackComplete)
{
	this->onAttackTelegraphBegin();

	this->runAction(Sequence::create(
		DelayTime::create(this->getAttackDuration()),
		CallFunc::create([=]()
		{
			switch (this->attackType)
			{
				default:
				case AttackType::Damage:
				case AttackType::Healing:
				{
					this->doDamageOrHealing(owner, target);

					break;
				}
				case AttackType::ProjectileDamage:
				case AttackType::ProjectileHealing:
				{
					this->generateProjectiles(owner, target);
				}
			}
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

void PlatformerAttack::generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target)
{
}

void PlatformerAttack::onAttackEnd()
{
}

void PlatformerAttack::onCleanup()
{
}

void PlatformerAttack::replaceWeaponWithProjectile(PlatformerEntity* owner, Projectile* projectile)
{
	AnimationPart* weapon = owner->getAnimations()->getAnimationPart("mainhand");

	if (weapon != nullptr)
	{
		weapon->replaceWithObject(projectile, 2.0f);
	}

	projectile->setPosition3D(GameUtils::getWorldCoords3D(weapon == nullptr ? (Node*)owner : (Node*)weapon));

	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
		owner,
		projectile,
		ObjectEvents::SpawnMethod::Above,
		ObjectEvents::PositionMode::Retain
	));
}

int PlatformerAttack::getRandomDamageOrHealing()
{
	return RandomHelper::random_int(this->getBaseDamageOrHealingMin(), this->getBaseDamageOrHealingMax());
}

int PlatformerAttack::getBaseDamageOrHealingMin()
{
	return this->baseDamageOrHealingMin;
}

int PlatformerAttack::getBaseDamageOrHealingMax()
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
