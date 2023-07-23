#include "RobotClaw.h"

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

const std::string RobotClaw::MapKey = "robot-claw";

RobotClaw* RobotClaw::create(ValueMap& properties)
{
	RobotClaw* instance = new RobotClaw(properties);
	
	instance->autorelease();

	return instance;
}

RobotClaw::RobotClaw(ValueMap& properties) : super(properties)
{
	this->mineClawAnimations = SmartAnimationNode::create(ObjectResources::Decor_RobotClaw_Animations);

	this->mineClawAnimations->setPositionY(-GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat() / 2.0f);

	this->addChild(this->mineClawAnimations);
}

RobotClaw::~RobotClaw()
{
}

void RobotClaw::onEnter()
{
	super::onEnter();

	this->mineClawAnimations->playAnimation("RaiseAndDrop", SmartAnimationNode::AnimationPlayMode::Repeat);
}

void RobotClaw::initializePositions()
{
	super::initializePositions();
}

void RobotClaw::initializeListeners()
{
	super::initializeListeners();
}
