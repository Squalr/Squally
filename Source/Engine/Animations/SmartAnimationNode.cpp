#include "SmartAnimationNode.h"

#include <algorithm>

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"

using namespace cocos2d;

const std::string SmartAnimationNode::DefaultAnimationEntityName = "Entity";
const std::string SmartAnimationNode::DefaultAnimationName = "Idle";

SmartAnimationNode* SmartAnimationNode::create(std::string animationResource)
{
	return SmartAnimationNode::create(animationResource, SmartAnimationNode::DefaultAnimationEntityName);
}

SmartAnimationNode* SmartAnimationNode::create(std::string animationResource, std::string entityName)
{
	SmartAnimationNode* instance = new SmartAnimationNode(animationResource, entityName);

	instance->autorelease();

	return instance;
}

SmartAnimationNode::SmartAnimationNode(std::string animationResource, std::string entityName)
{
	this->animationResource = animationResource;
	this->entityName = entityName;
	this->animationParts = std::map<std::string, AnimationPart*>();
	this->initialized = false;
	this->currentAnimation = "";
	this->currentAnimationPriority = -1.0f;
	this->spriterAnimation = SpriterAnimationNode::create(animationResource, entityName);

	if (this->spriterAnimation != nullptr)
	{
		this->addChild(this->spriterAnimation);
	}
}

SmartAnimationNode::~SmartAnimationNode()
{
}

SmartAnimationNode* SmartAnimationNode::clone()
{
	return SmartAnimationNode::create(this->animationResource, this->entityName);
}

void SmartAnimationNode::playAnimation(AnimationPlayMode animationPlayMode, AnimParams animParams, std::function<void()> callback)
{
	this->playAnimation(SmartAnimationNode::DefaultAnimationName, animationPlayMode, animParams, callback);
}

void SmartAnimationNode::playAnimation(std::string animationName, AnimationPlayMode animationPlayMode, AnimParams animParams, std::function<void()> callback)
{
	if (animParams.priority <= this->currentAnimationPriority && !animParams.cancelAnim)
	{
		return;
	}

	this->currentAnimationPriority = animParams.priority;

	if (this->spriterAnimation != nullptr)
	{
		if (!this->initialized || animParams.cancelAnim || this->currentAnimation != animationName)
		{
			this->initialized = true;
			this->currentAnimation = animationName;
			this->spriterAnimation->playAnimation(animationName);
		}

		switch (animationPlayMode)
		{
			case AnimationPlayMode::ReturnToIdle:
			{
				this->spriterAnimation->setRepeating(false);
				this->spriterAnimation->setAnimationCompleteCallback([=]()
				{
					this->clearAnimationPriority();
					this->playAnimation(AnimationPlayMode::ReturnToIdle);
				});
				break;
			}
			case AnimationPlayMode::PauseOnAnimationComplete:
			{
				this->spriterAnimation->setRepeating(false);
				this->spriterAnimation->setAnimationCompleteCallback([=]()
				{
					this->spriterAnimation->setPlaybackPaused(true);
				});
				break;
			}
			case AnimationPlayMode::Callback:
			{
				this->spriterAnimation->setRepeating(false);
				this->spriterAnimation->setAnimationCompleteCallback([=]()
				{
					if (callback != nullptr)
					{
						callback();
					}
				});
				break;
			}
			default:
			case AnimationPlayMode::Repeat:
			{
				this->spriterAnimation->setRepeating(true);
				this->spriterAnimation->setAnimationCompleteCallback(nullptr);
				break;
			}
		}
	}
}

void SmartAnimationNode::clearAnimationPriority()
{
	this->currentAnimationPriority = -1.0f;
}

AnimationPart* SmartAnimationNode::getAnimationPart(std::string partName)
{
	if (this->animationParts.find(partName) != this->animationParts.end())
	{
		return this->animationParts[partName];
	}

	AnimationPart* animationPart = nullptr;

	if (this->spriterAnimation != nullptr)
	{
		if (SpriterAnimationPart* spriterAnimationPart = this->spriterAnimation->getPartByName(partName))
		{
			animationPart = AnimationPart::create(spriterAnimationPart);
		}
	}

	if (animationPart == nullptr)
	{
		return nullptr;
	}

	this->animationParts[partName] = animationPart;

	this->addChild(animationPart);

	return animationPart;
}

void SmartAnimationNode::restoreAnimationPart(std::string partName)
{
	if (this->animationParts.find(partName) != this->animationParts.end())
	{
		this->animationParts[partName]->reattachToTimeline();
		return;
	}

	if (this->spriterAnimation == nullptr)
	{
		return;
	}

	SpriterAnimationPart* animVariable = this->spriterAnimation->getPartByName(partName);

	if (animVariable != nullptr)
	{
		animVariable->setTimelineCanUpdate(true);
	}
}

void SmartAnimationNode::setFlippedX(bool flippedX)
{
	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->setFlippedX(flippedX);
	}
}

void SmartAnimationNode::setFlippedY(bool flippedY)
{
	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->setFlippedY(flippedY);
	}
}

bool SmartAnimationNode::getFlippedX()
{
	if (this->spriterAnimation != nullptr)
	{
		return this->spriterAnimation->getFlippedX();
	}
	
	return false;
}

bool SmartAnimationNode::getFlippedY()
{
	if (this->spriterAnimation != nullptr)
	{
		return this->spriterAnimation->getFlippedY();
	}
	
	return false;
}

std::string SmartAnimationNode::getCurrentAnimation()
{
	return this->currentAnimation;
}

std::string SmartAnimationNode::getAnimationResource()
{
	return this->animationResource;
}

void SmartAnimationNode::refreshCurrentAnimationState()
{
	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->refreshCurrentEntityAnimationState();
	}
}

void SmartAnimationNode::seekAnimationTimeRatio(float timeRatio)
{
	const float clampedTimeRatio = std::max(0.0f, std::min(1.0f, timeRatio));

	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->seekAnimationTimeRatio(clampedTimeRatio);
	}
}

void SmartAnimationNode::disableRender()
{
	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->setVisible(false);
	}
}

void SmartAnimationNode::enableRender()
{
	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->setVisible(true);
	}
}
