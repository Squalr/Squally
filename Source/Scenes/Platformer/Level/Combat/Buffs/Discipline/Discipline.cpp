#include "Discipline.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

#include "Resources/FXResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

Discipline* Discipline::create(PlatformerEntity* caster)
{
	Discipline* instance = new Discipline(caster);

	instance->autorelease();

	return instance;
}

Discipline::Discipline(PlatformerEntity* caster)
	: super(caster, caster, UIResources::Menus_Icons_HeartPurple, AbilityType::Arcane, BuffData("disciline-skill"))
{
	this->disciplineEffect = Sprite::create(FXResources::Auras_TriAura);

	this->disciplineEffect->setColor(Color3B::YELLOW);

	this->addChild(this->disciplineEffect);
}

Discipline::~Discipline()
{
}

void Discipline::onEnter()
{
	super::onEnter();
}

void Discipline::initializePositions()
{
	super::initializePositions();

	this->disciplineEffect->runAction(RepeatForever::create(Sequence::create(
		ScaleTo::create(0.5f, 0.95f),
		ScaleTo::create(0.5f, 1.0f),
		nullptr
	)));
}

void Discipline::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);

	this->onDamageTakenOrCycle(true);
}

void Discipline::onTimelineReset(CombatEvents::TimelineResetArgs* timelineReset)
{
	super::onTimelineReset(timelineReset);

	this->resetCount++;
	this->onDamageTakenOrCycle(false);
}


void Discipline::onDamageTakenOrCycle(bool isDamage)
{
	if (isDamage || this->resetCount >= 2)
	{
		this->removeBuff();
	}
}
