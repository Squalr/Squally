#include "PlatformerAttack.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

using namespace cocos2d;

const float PlatformerAttack::DefaultCleanupDuration = 5.0f;

PlatformerAttack::PlatformerAttack(AttackType attackType, std::string iconResource, int baseDamageOrHealingMin, int baseDamageOrHealingMax, int specialCost, float attackDuration, float recoverDuration, float cleanupDuration)
{
	this->attackType = attackType;
	this->iconResource = iconResource;
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

void PlatformerAttack::execute(PlatformerEntity* owner, PlatformerEntity* target, std::function<void(PlatformerEntity* target, int damageOrHealing)> onDamageOrHealingDelt, std::function<void()> onAttackComplete)
{
	this->onAttackTelegraphBegin();

	this->runAction(Sequence::create(
		DelayTime::create(this->getAttackDuration()),
		CallFunc::create([=]()
		{
			switch (this->attackType)
			{
				default:
				case AttackType::Direct:
				{
					onDamageOrHealingDelt(target, this->getRandomDamageOrHealing());
					this->onDamageOrHealingDelt();

					break;
				}
				case AttackType::Projectile:
				{
					this->generateProjectiles(owner, target, [=](PlatformerEntity* newTarget)
					{
						onDamageOrHealingDelt(newTarget, this->getRandomDamageOrHealing());
						this->onDamageOrHealingDelt();
					});
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

void PlatformerAttack::onDamageOrHealingDelt()
{
}

void PlatformerAttack::generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target, std::function<void(PlatformerEntity* target)> onTargetHit)
{
}

void PlatformerAttack::onAttackEnd()
{
}

void PlatformerAttack::onCleanup()
{
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
