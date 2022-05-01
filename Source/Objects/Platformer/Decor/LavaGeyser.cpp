#include "LavaGeyser.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LavaGeyser::MapKey = "lava-geyser";

LavaGeyser* LavaGeyser::create(ValueMap& properties)
{
	LavaGeyser* instance = new LavaGeyser(properties);
	
	instance->autorelease();

	return instance;
}

LavaGeyser::LavaGeyser(ValueMap& properties) : super(properties)
{
	this->baseAnimation = SmartAnimationSequenceNode::create();
	this->topAnimation = SmartAnimationSequenceNode::create();
	this->midAnimations = std::vector<SmartAnimationSequenceNode*>();

	this->addChild(this->baseAnimation);
	this->addChild(this->topAnimation);
}

LavaGeyser::~LavaGeyser()
{
}

void LavaGeyser::initializePositions()
{
	super::initializePositions();
}

void LavaGeyser::runAnimation()
{
	const std::vector<std::string>& animationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(ObjectResources::Decor_LavaBubble_Bubble_0000);
	this->baseAnimation->playAnimation(animationFiles, RandomHelper::random_real(0.045f, 0.11f), true);
}
