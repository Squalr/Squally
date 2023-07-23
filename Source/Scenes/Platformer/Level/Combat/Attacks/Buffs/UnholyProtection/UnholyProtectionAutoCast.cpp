#include "UnholyProtectionAutoCast.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/UnholyProtection/UnholyProtection.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string UnholyProtectionAutoCast::UnholyProtectionAutoCastIdentifier = "unholy-protection-auto-cast";

UnholyProtectionAutoCast* UnholyProtectionAutoCast::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	UnholyProtectionAutoCast* instance = new UnholyProtectionAutoCast(caster, target);

	instance->autorelease();

	return instance;
}

UnholyProtectionAutoCast::UnholyProtectionAutoCast(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, "", AbilityType::Shadow, BuffData(-1.0f, UnholyProtectionAutoCast::UnholyProtectionAutoCastIdentifier, 0.0f))
{
	this->hasAutoCasted = false;
}

UnholyProtectionAutoCast::~UnholyProtectionAutoCast()
{
}

void UnholyProtectionAutoCast::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	if (this->hasAutoCasted)
	{
		return;
	}

	int originalHealth = damageOrHealing->target->getRuntimeStateOrDefaultInt(StateKeys::Health, 0);
	int projectedNewHealth = originalHealth - damageOrHealing->damageOrHealingValue;

	if (projectedNewHealth <= 0)
	{
		damageOrHealing->target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			this->hasAutoCasted = true;

			entityBuffBehavior->applyBuff(UnholyProtection::create(damageOrHealing->target, damageOrHealing->target));
			entityBuffBehavior->getBuff<UnholyProtection>([&](UnholyProtection* unholyProtection)
			{
				unholyProtection->onBeforeDamageTaken(damageOrHealing);

				damageOrHealing->target->getComponent<EntityManaBehavior>([=](EntityManaBehavior* manaBehavior)
				{
					manaBehavior->setMana(0);
				});
			});
		});
	}
}

void UnholyProtectionAutoCast::onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeHealingTaken(damageOrHealing);

	if (this->hasAutoCasted)
	{
		return;
	}

	int originalHealth = damageOrHealing->target->getRuntimeStateOrDefaultInt(StateKeys::Health, 0);
	int projectedNewHealth = originalHealth + damageOrHealing->damageOrHealingValue;

	if (projectedNewHealth <= 0)
	{
		damageOrHealing->target->getComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			this->hasAutoCasted = true;

			entityBuffBehavior->applyBuff(UnholyProtection::create(damageOrHealing->target, damageOrHealing->target));
			entityBuffBehavior->getBuff<UnholyProtection>([&](UnholyProtection* unholyProtection)
			{
				unholyProtection->onBeforeHealingTaken(damageOrHealing);

				damageOrHealing->target->getComponent<EntityManaBehavior>([=](EntityManaBehavior* manaBehavior)
				{
					manaBehavior->setMana(0);
				});
			});
		});
	}
}
