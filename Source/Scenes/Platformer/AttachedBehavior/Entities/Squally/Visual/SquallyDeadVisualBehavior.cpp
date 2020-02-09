#include "SquallyDeadVisualBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyDeadVisualBehavior::MapKeyAttachedBehavior = "squally-dead-visuals";

SquallyDeadVisualBehavior* SquallyDeadVisualBehavior::create(GameObject* owner)
{
	SquallyDeadVisualBehavior* instance = new SquallyDeadVisualBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyDeadVisualBehavior::SquallyDeadVisualBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyDeadVisualBehavior::~SquallyDeadVisualBehavior()
{
}

void SquallyDeadVisualBehavior::onLoad()
{
	this->squally->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		AnimationPart* leftEye = this->squally->getAnimations()->getAnimationPart("eye_left");
		AnimationPart* rightEye = this->squally->getAnimations()->getAnimationPart("eye_right");
		AnimationPart* mouth = this->squally->getAnimations()->getAnimationPart("mouth");

		if (mouth != nullptr && !value.asBool())
		{
			mouth->replaceSprite(EntityResources::Squally_MOUTH_DEAD);
		}
		
		if (leftEye != nullptr)
		{
			if (value.asBool())
			{
				leftEye->replaceSprite(EntityResources::Squally_EYE_L);
			}
			else
			{
				leftEye->replaceSprite(EntityResources::Squally_Eye_Dead_L);
			}
		}
		
		if (rightEye != nullptr)
		{
			if (value.asBool())
			{
				rightEye->replaceSprite(EntityResources::Squally_Eye_R);
			}
			else
			{
				rightEye->replaceSprite(EntityResources::Squally_Eye_Dead_R);
			}
		}
	});
}
