#include "UndyingAutoCast.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Undying/Undying.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_UNDYING 1

const std::string UndyingAutoCast::UndyingAutoCastIdentifier = "undying-auto-cast";

UndyingAutoCast* UndyingAutoCast::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	UndyingAutoCast* instance = new UndyingAutoCast(caster, target);

	instance->autorelease();

	return instance;
}

UndyingAutoCast::UndyingAutoCast(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, "", AbilityType::Shadow, BuffData(-1.0f, UndyingAutoCast::UndyingAutoCastIdentifier))
{
	this->hasAutoCasted = false;
}

UndyingAutoCast::~UndyingAutoCast()
{
}

void UndyingAutoCast::onBeforeDamageTaken(CombatEvents::ModifyableDamageOrHealing damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	if (this->hasAutoCasted)
	{
		return;
	}

	int originalHealth = damageOrHealing.target->getRuntimeStateOrDefaultInt(StateKeys::Health, 0);
	int projectedNewHealth = originalHealth - damageOrHealing.originalDamageOrHealing;

	if (projectedNewHealth <= 0)
	{
		damageOrHealing.target->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			this->hasAutoCasted = true;

			entityBuffBehavior->applyBuff(Undying::create(damageOrHealing.target, damageOrHealing.target));
			entityBuffBehavior->getBuff<Undying>([&](Undying* undying)
			{
				undying->onBeforeDamageTaken(damageOrHealing);
			});
		});
	}
}

void UndyingAutoCast::onBeforeHealingTaken(CombatEvents::ModifyableDamageOrHealing damageOrHealing)
{
	super::onBeforeHealingTaken(damageOrHealing);

	if (this->hasAutoCasted)
	{
		return;
	}

	int originalHealth = damageOrHealing.target->getRuntimeStateOrDefaultInt(StateKeys::Health, 0);
	int projectedNewHealth = originalHealth + damageOrHealing.originalDamageOrHealing;

	if (projectedNewHealth <= 0)
	{
		damageOrHealing.target->getAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
		{
			this->hasAutoCasted = true;

			entityBuffBehavior->applyBuff(Undying::create(damageOrHealing.target, damageOrHealing.target));
			entityBuffBehavior->getBuff<Undying>([&](Undying* undying)
			{
				undying->onBeforeHealingTaken(damageOrHealing);
			});
		});
	}
}
