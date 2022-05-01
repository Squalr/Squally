#include "LavaFX.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LavaFX::MapKey = "lava-fx";

LavaFX* LavaFX::create(ValueMap& properties)
{
	LavaFX* instance = new LavaFX(properties);
	
	instance->autorelease();

	return instance;
}

LavaFX::LavaFX(ValueMap& properties) : super(properties)
{
	this->fxAnimations = SmartAnimationSequenceNode::create();

	this->addChild(this->fxAnimations);
}

LavaFX::~LavaFX()
{
}

void LavaFX::initializePositions()
{
	super::initializePositions();
}

void LavaFX::runAnimation()
{
	if (RandomHelper::random_real(0.0f, 1.0f) < 0.65f) // Controls the ratio of bubbles to whisps
	{
		const std::vector<std::string>& animationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(ObjectResources::Decor_LavaBubble_Bubble_0000);
		this->fxAnimations->playAnimation(animationFiles, RandomHelper::random_real(0.045f, 0.11f), true);
	}
	else
	{
		const std::vector<std::string>& animationFiles = SmartAnimationSequenceNode::GetAllAnimationFiles(ObjectResources::Decor_LavaWhisp_Whisp_0000);
		this->fxAnimations->playAnimation(animationFiles, RandomHelper::random_real(0.025f, 0.075f), true);
	}
}
