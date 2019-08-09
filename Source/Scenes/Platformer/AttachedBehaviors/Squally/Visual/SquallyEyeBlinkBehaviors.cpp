#include "SquallyEyeBlinkBehaviors.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Entities/Platformer/Squally/Squally.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyEyeBlinkBehaviors::MapKeyAttachedBehavior = "squally-equipment-visuals";

SquallyEyeBlinkBehaviors* SquallyEyeBlinkBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyEyeBlinkBehaviors* instance = new SquallyEyeBlinkBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyEyeBlinkBehaviors::SquallyEyeBlinkBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->squally = static_cast<Squally*>(owner);

	this->leftEyeController = SmartAnimationSequenceNode::create();
	this->rightEyeController = SmartAnimationSequenceNode::create();

	if (this->squally == nullptr)
	{
		this->invalidate();
	}

	this->leftEyeController->setVisible(false);
	this->rightEyeController->setVisible(false);
	
	this->addChild(this->leftEyeController);
	this->addChild(this->rightEyeController);
}

SquallyEyeBlinkBehaviors::~SquallyEyeBlinkBehaviors()
{
}

void SquallyEyeBlinkBehaviors::onLoad()
{
	this->runEyeBlinkLoop();
}

void SquallyEyeBlinkBehaviors::runEyeBlinkLoop()
{
	const float BlinkSpeed = 0.0075f;
	const float EyesClosedDuration = 0.015f;
	const float TimeBetweenBlinks = 5.5f;
	
	this->leftEyeController->playAnimationAndReverseRepeat(EntityResources::Squally_Blink_EYE_L_Blink_0000, BlinkSpeed, EyesClosedDuration, BlinkSpeed, TimeBetweenBlinks);
	this->leftEyeController->getForwardsAnimation()->incrementCallback = [=](int current, int max, std::string spriteResource)
	{
		AnimationPart* leftEye = this->squally->getAnimations()->getAnimationPart("eye_left");
		
		if (leftEye != nullptr)
		{
			leftEye->replaceSprite(spriteResource);
		}

		return current + 1;
	};
	this->leftEyeController->getBackwardsAnimation()->incrementCallback = [=](int current, int max, std::string spriteResource)
	{
		AnimationPart* leftEye = this->squally->getAnimations()->getAnimationPart("eye_left");
		
		if (leftEye != nullptr)
		{
			leftEye->replaceSprite(spriteResource);
		}

		return current + 1;
	};
	this->rightEyeController->playAnimationAndReverseRepeat(EntityResources::Squally_Blink_EYE_L_Blink_0000, BlinkSpeed, EyesClosedDuration, BlinkSpeed, TimeBetweenBlinks);
	this->rightEyeController->getForwardsAnimation()->incrementCallback = [=](int current, int max, std::string spriteResource)
	{
		AnimationPart* rightEye = this->squally->getAnimations()->getAnimationPart("eye_right");
		
		if (rightEye != nullptr)
		{
			rightEye->replaceSprite(spriteResource);
		}

		return current + 1;
	};
	this->rightEyeController->getBackwardsAnimation()->incrementCallback = [=](int current, int max, std::string spriteResource)
	{
		AnimationPart* rightEye = this->squally->getAnimations()->getAnimationPart("eye_right");
		
		if (rightEye != nullptr)
		{
			rightEye->replaceSprite(spriteResource);
		}

		return current + 1;
	};
}
