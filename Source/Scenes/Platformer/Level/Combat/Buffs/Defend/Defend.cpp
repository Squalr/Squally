#include "Defend.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

#include "Resources/FXResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const float Defend::DamageReduction = 0.75f;

Defend* Defend::create(PlatformerEntity* caster)
{
	Defend* instance = new Defend(caster);

	instance->autorelease();

	return instance;
}

Defend::Defend(PlatformerEntity* caster) : super(caster, caster)
{
	this->defendEffect = SmartAnimationSequenceNode::create(FXResources::EnergyCircle_EnergyCircle_0000);

	this->addChild(this->defendEffect);
}

Defend::~Defend()
{
}

void Defend::onEnter()
{
	super::onEnter();

	this->defendEffect->playAnimationRepeat(FXResources::EnergyCircle_EnergyCircle_0000, 0.05f);
}

void Defend::initializePositions()
{
	super::initializePositions();
}

void Defend::onBeforeDamageTaken(int* damageOrHealing, std::function<void()> handleCallback)
{
	super::onBeforeDamageTaken(damageOrHealing, handleCallback);

	*damageOrHealing = int(std::round(float(*damageOrHealing) * Defend::DamageReduction));
}

void Defend::onTimelineReset(bool wasInterrupt)
{
	super::onTimelineReset(wasInterrupt);

	this->removeBuff();
}
