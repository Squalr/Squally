#include "LavaBubbles.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LavaBubbles::MapKey = "lava-bubbles";

LavaBubbles* LavaBubbles::create(ValueMap& properties)
{
	LavaBubbles* instance = new LavaBubbles(properties);
	
	instance->autorelease();

	return instance;
}

LavaBubbles::LavaBubbles(ValueMap& properties) : super(properties)
{
	this->bubbleAnimations = SmartAnimationSequenceNode::create();

	this->addChild(this->bubbleAnimations);
}

LavaBubbles::~LavaBubbles()
{
}

void LavaBubbles::initializePositions()
{
	super::initializePositions();
}

void LavaBubbles::runAnimation()
{
	const std::vector<std::string>& animationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(ObjectResources::Decor_LavaBubble_Bubble_0000);
	this->bubbleAnimations->playAnimation(animationFiles, 0.25f, true);
}
