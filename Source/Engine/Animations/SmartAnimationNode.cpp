#include "SmartAnimationNode.h"

#include <algorithm>

#include <spriter2dx/AnimationNode.h>

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"

using namespace cocos2d;
using namespace Spriter2dX;

const std::string SmartAnimationNode::DefaultAnimationEntityName = "Entity";
const std::string SmartAnimationNode::DefaultAnimationName = "Idle";

SmartAnimationNode* SmartAnimationNode::create(std::string animationResource)
{
	return SmartAnimationNode::create(animationResource, SmartAnimationNode::DefaultAnimationEntityName);
}

SmartAnimationNode* SmartAnimationNode::create(std::string animationResource, std::string entityName)
{
	return SmartAnimationNode::create(animationResource, entityName, true);
}

SmartAnimationNode* SmartAnimationNode::create(std::string animationResource, std::string entityName, bool useNewAnimationSystem)
{
	SmartAnimationNode* instance = new SmartAnimationNode(animationResource, entityName, useNewAnimationSystem);

	instance->autorelease();

	return instance;
}

SmartAnimationNode::SmartAnimationNode(std::string animationResource, std::string entityName, bool useNewAnimationSystem)
{
	this->animationResource = animationResource;
	this->entityName = entityName;
	this->animationParts = std::map<std::string, AnimationPart*>();
	this->initialized = false;
	this->currentAnimation = "";
	this->currentAnimationPriority = -1.0f;
	this->entity = nullptr;
	this->useNewAnimationSystem = useNewAnimationSystem;

	if (this->useNewAnimationSystem)
	{
		this->spriterAnimation = SpriterAnimationNode::create(animationResource, entityName);
		this->animationNode = nullptr;
	}
	else
	{
		this->animationNode = AnimationNode::create(animationResource);
		this->spriterAnimation = nullptr;
		this->entity = this->animationNode->play(entityName);
	}
	
	if (this->animationNode != nullptr)
	{
		this->addChild(this->animationNode);
	}

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
	return SmartAnimationNode::create(this->animationResource, this->entityName, this->useNewAnimationSystem);
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

	if (this->entity == nullptr)
	{
		return;
	}
	
	if (this->entity->hasAnimation(animationName))
	{
		if (!this->initialized || animParams.cancelAnim || this->entity->currentAnimationName() != animationName)
		{
			this->initialized = true;
			this->entity->setCurrentTime(0.0f);
			this->entity->setCurrentAnimation(animationName, animParams.blendTime);
			this->entity->reprocessCurrentTime();
			this->entity->render();
			this->currentAnimation = animationName;
		}

		switch (animationPlayMode)
		{
			case AnimationPlayMode::ReturnToIdle:
			{
				this->entity->setAnimationCompleteCallback([=]()
				{
					this->clearAnimationPriority();

					this->playAnimation(AnimationPlayMode::ReturnToIdle);
				});

				break;
			}
			case AnimationPlayMode::PauseOnAnimationComplete:
			{
				this->entity->setAnimationCompleteCallback([=]()
				{
					this->entity->pausePlayback();
				});

				break;
			}
			case AnimationPlayMode::Callback:
			{
				this->entity->setAnimationCompleteCallback([=]()
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
				this->entity->setAnimationCompleteCallback([=]()
				{
					float priority = this->currentAnimationPriority;
					this->initialized = false;
					this->clearAnimationPriority();

					this->playAnimation(this->getCurrentAnimation(), AnimationPlayMode::Repeat, priority);
				});
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

	if (this->entity != nullptr)
	{
		animationPart = AnimationPart::create(this->entity, partName);
	}
	else if (this->spriterAnimation != nullptr)
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

	if (this->entity == nullptr)
	{
		return;
	}

	auto animVariable = this->entity->getObjectInstance(partName);

	if (animVariable != nullptr)
	{
		animVariable->toggleTimelineCanUpdate(true);
	}
}

void SmartAnimationNode::setFlippedX(bool flippedX)
{
	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->setFlippedX(flippedX);
	}

	if (this->animationNode == nullptr)
	{
		return;
	}

	this->animationNode->setFlippedX(flippedX);
}

void SmartAnimationNode::setFlippedY(bool flippedY)
{
	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->setFlippedY(flippedY);
	}

	if (this->animationNode == nullptr)
	{
		return;
	}
	
	this->animationNode->setFlippedY(flippedY);
}

bool SmartAnimationNode::getFlippedX()
{
	if (this->spriterAnimation != nullptr)
	{
		return this->spriterAnimation->getFlippedX();
	}

	if (this->animationNode == nullptr)
	{
		return false;
	}
	
	return this->animationNode->getFlippedX();
}

bool SmartAnimationNode::getFlippedY()
{
	if (this->spriterAnimation != nullptr)
	{
		return this->spriterAnimation->getFlippedY();
	}

	if (this->animationNode == nullptr)
	{
		return false;
	}
	
	return this->animationNode->getFlippedY();
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

	if (this->entity != nullptr)
	{
		this->entity->reprocessCurrentTime();
		this->entity->render();
	}
}

void SmartAnimationNode::seekAnimationTimeRatio(float timeRatio)
{
	const float clampedTimeRatio = std::max(0.0f, std::min(1.0f, timeRatio));

	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->seekAnimationTimeRatio(clampedTimeRatio);
		return;
	}

	if (this->entity != nullptr)
	{
		this->entity->setTimeRatio(clampedTimeRatio);
		this->entity->reprocessCurrentTime();
		this->entity->render();
	}
}

void SmartAnimationNode::disableRender()
{
	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->setVisible(false);
	}

	if (this->animationNode == nullptr)
	{
		return;
	}

	this->animationNode->disableRender();
}

void SmartAnimationNode::enableRender()
{
	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->setVisible(true);
	}

	if (this->animationNode == nullptr)
	{
		return;
	}
	
	this->animationNode->enableRender();
}
