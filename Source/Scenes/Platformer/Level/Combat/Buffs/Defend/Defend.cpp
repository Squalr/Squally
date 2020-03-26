#include "Defend.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

const float Defend::DamageReduction = 0.75f;

Defend* Defend::create(PlatformerEntity* caster)
{
	Defend* instance = new Defend(caster);

	instance->autorelease();

	return instance;
}

Defend::Defend(PlatformerEntity* caster) : super(caster, caster, BuffData("defend-skill"))
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

	this->defendEffect->setPosition(this->caster->getEntityCenterPoint());

	this->defendEffect->runAction(RepeatForever::create(Sequence::create(
		ScaleTo::create(0.5f, 0.95f),
		ScaleTo::create(0.5f, 1.0f),
		nullptr
	)));
}

void Defend::onBeforeDamageTaken(int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target)
{
	super::onBeforeDamageTaken(damageOrHealing, handleCallback, caster, target);
	
	*damageOrHealing = int(std::round(float(*damageOrHealing) * (1.0f - Defend::DamageReduction)));

	CombatEvents::TriggerCastBlocked(CombatEvents::CastBlockedArgs(this->caster));

	this->onDamageTakenOrCycle(true);
}

void Defend::onTimelineReset(bool wasInterrupt)
{
	super::onTimelineReset(wasInterrupt);

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
