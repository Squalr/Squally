#include "MineClaw.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MineClaw::MapKey = "mine-claw";

MineClaw* MineClaw::create(ValueMap& properties)
{
	MineClaw* instance = new MineClaw(properties);
	
	instance->autorelease();

	return instance;
}

MineClaw::MineClaw(ValueMap& properties) : super(properties)
{
	this->mineClawAnimations = SmartAnimationNode::create(ObjectResources::Decor_MineClaw_Animations);

	this->mineClawAnimations->setPositionY(-GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat() / 2.0f);

	this->addChild(this->mineClawAnimations);
}

MineClaw::~MineClaw()
{
}

void MineClaw::onEnter()
{
	super::onEnter();

	this->mineClawAnimations->playAnimation("RaiseAndDrop", SmartAnimationNode::AnimationPlayMode::Repeat);
}

void MineClaw::initializePositions()
{
	super::initializePositions();
}

void MineClaw::initializeListeners()
{
	super::initializeListeners();
}
