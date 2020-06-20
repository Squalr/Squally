#include "Defend.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

#include "Resources/FXResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const float Defend::DamageReduction = 0.5f;

Defend* Defend::create(PlatformerEntity* caster)
{
	Defend* instance = new Defend(caster);

	instance->autorelease();

	return instance;
}

Defend::Defend(PlatformerEntity* caster)
	: super(caster, caster, UIResources::Menus_Icons_Shield, AbilityType::Physical, BuffData("defend-skill"))
{
	this->defendEffect = Sprite::create(FXResources::Auras_DefendAura);
	this->resetCount = 0;

	this->addChild(this->defendEffect);
}

Defend::~Defend()
{
}

void Defend::onEnter()
{
	super::onEnter();
}

void Defend::initializePositions()
{
	super::initializePositions();

	this->defendEffect->runAction(RepeatForever::create(Sequence::create(
		ScaleTo::create(0.5f, 0.95f),
		ScaleTo::create(0.5f, 1.0f),
		nullptr
	)));
}

void Defend::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);
	
	(*damageOrHealing->damageOrHealing) = int(std::round(float(damageOrHealing->damageOrHealingValue) * (1.0f - Defend::DamageReduction)));

	CombatEvents::TriggerCastBlocked(CombatEvents::CastBlockedArgs(this->caster));

	this->onDamageTakenOrCycle(true);
}

void Defend::onTimelineReset(CombatEvents::TimelineResetArgs* timelineReset)
{
	super::onTimelineReset(timelineReset);

	this->resetCount++;
	this->onDamageTakenOrCycle(false);
}


void Defend::onDamageTakenOrCycle(bool isDamage)
{
	if (isDamage || this->resetCount >= 2)
	{
		this->removeBuff();
	}
}
