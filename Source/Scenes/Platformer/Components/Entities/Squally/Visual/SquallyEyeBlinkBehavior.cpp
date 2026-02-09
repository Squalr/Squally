#include "SquallyEyeBlinkBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Utils/LogUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyEyeBlinkBehavior::MapKey = "squally-eye-blink";

SquallyEyeBlinkBehavior* SquallyEyeBlinkBehavior::create(GameObject* owner)
{
	SquallyEyeBlinkBehavior* instance = new SquallyEyeBlinkBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyEyeBlinkBehavior::SquallyEyeBlinkBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);
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

SquallyEyeBlinkBehavior::~SquallyEyeBlinkBehavior()
{
}

void SquallyEyeBlinkBehavior::onLoad()
{
	this->runEyeBlinkLoop();
}

void SquallyEyeBlinkBehavior::onDisable()
{
	super::onDisable();
}

void SquallyEyeBlinkBehavior::runEyeBlinkLoop()
{
	const float BlinkSpeed = 0.0075f;
	const float EyesClosedDuration = 0.015f;
	const float TimeBetweenBlinks = 5.5f;
	
	this->leftEyeController->playAnimationAndReverseRepeat(EntityResources::Squally_Blink_EYE_L_Blink_0000, BlinkSpeed, EyesClosedDuration, BlinkSpeed, TimeBetweenBlinks);
	this->rightEyeController->playAnimationAndReverseRepeat(EntityResources::Squally_Blink_Eye_R_Blink_0000, BlinkSpeed, EyesClosedDuration, BlinkSpeed, TimeBetweenBlinks);
	
	this->leftEyeController->setSpriteChangeCallback([=](const std::string& spriteResource, int index)
	{
		AnimationPart* leftEye = this->squally->getAnimations()->getAnimationPart("eye_left");
		
		if (leftEye != nullptr)
		{
			if (this->squally->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				leftEye->replaceSprite(spriteResource);
			}
		}
		else
		{
			static bool hasLoggedMissingLeftEye = false;

			if (!hasLoggedMissingLeftEye)
			{
				hasLoggedMissingLeftEye = true;
				LogUtils::logError("Animation verification failed: Squally eye blink missing 'eye_left' animation part");
			}
		}
	});

	this->rightEyeController->setSpriteChangeCallback([=](const std::string& spriteResource, int index)
	{
		AnimationPart* rightEye = this->squally->getAnimations()->getAnimationPart("eye_right");
		
		if (rightEye != nullptr)
		{
			if (this->squally->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				rightEye->replaceSprite(spriteResource);
			}
		}
		else
		{
			static bool hasLoggedMissingRightEye = false;

			if (!hasLoggedMissingRightEye)
			{
				hasLoggedMissingRightEye = true;
				LogUtils::logError("Animation verification failed: Squally eye blink missing 'eye_right' animation part");
			}
		}
	});
}
