#include "LavaFall.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LavaFall::MapKey = "lava-fall";

LavaFall* LavaFall::create(ValueMap& properties)
{
	LavaFall* instance = new LavaFall(properties);
	
	instance->autorelease();

	return instance;
}

LavaFall::LavaFall(ValueMap& properties) : super(properties)
{
	this->animationLinks = std::vector<SmartAnimationSequenceNode*>();
}

LavaFall::~LavaFall()
{
}

void LavaFall::initializePositions()
{
	super::initializePositions();
}

void LavaFall::runAnimation()
{
	const std::vector<std::string>& animationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(ObjectResources::Decor_LavaBubble_Bubble_0000);

	for (SmartAnimationSequenceNode* next : this->animationLinks)
	{
		next->playAnimation(animationFiles, RandomHelper::random_real(0.045f, 0.11f), true);
	}
}
