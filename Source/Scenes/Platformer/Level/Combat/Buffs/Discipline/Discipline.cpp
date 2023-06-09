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

	this->disciplineEffect->setOpacity(0);
	this->disciplineEffect->runAction(Sequence::create(
		FadeTo::create(0.5f, 255),
		DelayTime::create(0.25f),
		FadeTo::create(0.5f, 0),
		nullptr
	));
}

void Discipline::initializePositions()
{
	super::initializePositions();
}

void Discipline::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	super::onBeforeDamageTaken(damageOrHealing);
}

void Discipline::onTimelineReset(CombatEvents::TimelineResetArgs* timelineReset)
{
	super::onTimelineReset(timelineReset);

	this->resetCount++;
	this->onCycle();
}


void Discipline::onCycle()
{
	if (this->resetCount >= 3)
	{
		this->removeBuff();
	}
}
