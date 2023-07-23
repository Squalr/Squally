#include "Thorns.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

#include "Resources/FXResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const float Thorns::DamageReduction = 0.5f;

Thorns* Thorns::create(PlatformerEntity* caster)
{
	Thorns* instance = new Thorns(caster);

	instance->autorelease();

	return instance;
}

Thorns::Thorns(PlatformerEntity* caster)
	: super(caster, caster, UIResources::Menus_Icons_ShieldThorned, AbilityType::Nature, BuffData("thorns-skill"))
{
	this->defendEffect = Sprite::create(FXResources::Auras_ThornsAura);

	this->addChild(this->defendEffect);
}

Thorns::~Thorns()
{
}

void Thorns::onEnter()
{
	super::onEnter();
}

void Thorns::initializePositions()
{
	super::initializePositions();

	this->defendEffect->runAction(RepeatForever::create(Sequence::create(
		ScaleTo::create(0.5f, 0.95f),
		ScaleTo::create(0.5f, 1.0f),
		nullptr
	)));
}

void Thorns::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);
	
	(*damageOrHealing->damageOrHealing) = int(std::round(float(damageOrHealing->damageOrHealingValue) * (1.0f - Thorns::DamageReduction)));

	CombatEvents::TriggerCastBlocked(CombatEvents::CastBlockedArgs(this->caster));

	// Reflect damage back to attacker (do not let buffs process this damage -- two reflect spells could infinite loop otherwise)
	CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(
		damageOrHealing->target,
		damageOrHealing->caster,
		5,
		AbilityType::Nature,
		true,
		false,
		false
	));

	this->onDamageTakenOrCycle(true);
}

void Thorns::onTimelineReset(CombatEvents::TimelineResetArgs* timelineReset)
{
	super::onTimelineReset(timelineReset);

	this->resetCount++;
	this->onDamageTakenOrCycle(false);
}


void Thorns::onDamageTakenOrCycle(bool isDamage)
{
	if (isDamage || this->resetCount >= 2)
	{
		this->removeBuff();
	}
}
