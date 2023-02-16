#include "ImmortalityAutoCast.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Immortality/Immortality.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_UNDYING 1

const std::string ImmortalityAutoCast::ImmortalityAutoCastIdentifier = "immortality-auto-cast";

ImmortalityAutoCast* ImmortalityAutoCast::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	ImmortalityAutoCast* instance = new ImmortalityAutoCast(caster, target);

	instance->autorelease();

	return instance;
}

ImmortalityAutoCast::ImmortalityAutoCast(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, "", AbilityType::Shadow, BuffData(-1.0f, ImmortalityAutoCast::ImmortalityAutoCastIdentifier, 0.0f))
{
	this->hasAutoCasted = false;
}

ImmortalityAutoCast::~ImmortalityAutoCast()
{
}

void ImmortalityAutoCast::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
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

			entityBuffBehavior->applyBuff(Immortality::create(damageOrHealing->target, damageOrHealing->target));
			entityBuffBehavior->getBuff<Immortality>([&](Immortality* undying)
			{
				undying->onBeforeDamageTaken(damageOrHealing);

				damageOrHealing->target->getComponent<EntityManaBehavior>([=](EntityManaBehavior* manaBehavior)
				{
					manaBehavior->setMana(0);
				});
			});
		});
	}
}

void ImmortalityAutoCast::onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
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

			entityBuffBehavior->applyBuff(Immortality::create(damageOrHealing->target, damageOrHealing->target));
			entityBuffBehavior->getBuff<Immortality>([&](Immortality* undying)
			{
				undying->onBeforeHealingTaken(damageOrHealing);

				damageOrHealing->target->getComponent<EntityManaBehavior>([=](EntityManaBehavior* manaBehavior)
				{
					manaBehavior->setMana(0);
				});
			});
		});
	}
}
