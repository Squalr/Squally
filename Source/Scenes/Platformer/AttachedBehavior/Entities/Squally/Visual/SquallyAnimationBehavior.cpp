#include "SquallyAnimationBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyAnimationBehavior::MapKey = "squally-animations";

SquallyAnimationBehavior* SquallyAnimationBehavior::create(GameObject* owner)
{
	SquallyAnimationBehavior* instance = new SquallyAnimationBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyAnimationBehavior::SquallyAnimationBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyAnimationBehavior::~SquallyAnimationBehavior()
{
}

void SquallyAnimationBehavior::onLoad()
{
}

void SquallyAnimationBehavior::onDisable()
{
	super::onDisable();
}

void SquallyAnimationBehavior::update(float dt)
{
	super::update(dt);

	PlatformerEntity::ControlState controlState = this->squally->getControlState();	
	
	switch (controlState)
	{
		default:
		case PlatformerEntity::ControlState::Normal:
		{
			if (this->squally->getAnimations()->getCurrentAnimation() == this->squally->getSwimAnimation())
			{
				this->squally->getAnimations()->clearAnimationPriority();
				this->squally->getAnimations()->playAnimation();
			}

			break;
		}
		case PlatformerEntity::ControlState::Swimming:
		{
			if (this->squally->getAnimations()->getCurrentAnimation() == this->squally->getJumpAnimation())
			{
				this->squally->getAnimations()->clearAnimationPriority();
			}
			
			break;
		}
	}
}
