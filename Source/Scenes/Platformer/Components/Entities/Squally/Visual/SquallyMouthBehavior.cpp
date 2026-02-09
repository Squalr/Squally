#include "SquallyMouthBehavior.h"

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

const std::string SquallyMouthBehavior::MapKey = "squally-mouth";

SquallyMouthBehavior* SquallyMouthBehavior::create(GameObject* owner)
{
	SquallyMouthBehavior* instance = new SquallyMouthBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyMouthBehavior::SquallyMouthBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyMouthBehavior::~SquallyMouthBehavior()
{
}

void SquallyMouthBehavior::onLoad()
{
	this->scheduleUpdate();
}

void SquallyMouthBehavior::onDisable()
{
	super::onDisable();
}

void SquallyMouthBehavior::update(float dt)
{
	super::update(dt);

	if (!this->squally->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		return;
	}

	PlatformerEntity::ControlState controlState = this->squally->getControlState();
	
	switch (controlState)
	{
		default:
		case PlatformerEntity::ControlState::Normal:
		{
			if (this->squally->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				AnimationPart* mouth = this->squally->getAnimations()->getAnimationPart("mouth");

				if (mouth != nullptr)
				{
					mouth->replaceSprite(EntityResources::Squally_MOUTH);
				}
				else
				{
					static bool hasLoggedMissingMouthPart = false;

					if (!hasLoggedMissingMouthPart)
					{
						hasLoggedMissingMouthPart = true;
						LogUtils::logError("Animation verification failed: Squally mouth behavior missing 'mouth' animation part");
					}
				}
			}

			break;
		}
		case PlatformerEntity::ControlState::Swimming:
		{
			if (this->squally->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				AnimationPart* mouth = this->squally->getAnimations()->getAnimationPart("mouth");
				
				if (mouth != nullptr)
				{
					mouth->replaceSprite(EntityResources::Squally_MOUTH_SWIMMING);
				}
				else
				{
					static bool hasLoggedMissingMouthPart = false;

					if (!hasLoggedMissingMouthPart)
					{
						hasLoggedMissingMouthPart = true;
						LogUtils::logError("Animation verification failed: Squally mouth behavior missing 'mouth' animation part");
					}
				}
			}
			
			break;
		}
	}
}
