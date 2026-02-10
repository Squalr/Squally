#include "SmartAnimationNode.h"

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
	this->entity = nullptr;

	static const bool UseNewAnimationSystem = true;

	if (UseNewAnimationSystem)
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
		if (!this->spriterAnimation->hasAnimation(animationName))
		{
			return;
		}

		this->spriterAnimation->setAnimationPaused(false);
		const bool shouldRestart = !this->initialized || animParams.cancelAnim || this->spriterAnimation->getCurrentAnimation() != animationName;

		if (shouldRestart)
		{
			this->initialized = true;
			this->spriterAnimation->playAnimation(animationName);
			this->currentAnimation = animationName;
		}

		const bool shouldReschedulePlayMode = shouldRestart || !this->hasActivePlayMode || this->activePlayMode != animationPlayMode;
		this->activePlayModeCallback = callback;

		if (shouldReschedulePlayMode)
		{
			this->schedulePlayModeCompletion(animationPlayMode);
		}

		this->hasActivePlayMode = true;
		this->activePlayMode = animationPlayMode;
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
		animationPart = AnimationPart::create(this->spriterAnimation, partName);
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
	if (this->entity != nullptr)
	{
		auto animVariable = this->entity->getObjectInstance(partName);

		if (animVariable != nullptr)
		{
			animVariable->toggleTimelineCanUpdate(true);
		}
		
		return;
	}

	AnimationPart* animationPart = this->getAnimationPart(partName);

	if (animationPart == nullptr)
	{
		return;
	}

	animationPart->reattachToTimeline();
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

void SmartAnimationNode::disableRender()
{
	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->disableRender();
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
		this->spriterAnimation->enableRender();
	}

	if (this->animationNode == nullptr)
	{
		return;
	}
	
	this->animationNode->enableRender();
}

void SmartAnimationNode::schedulePlayModeCompletion(AnimationPlayMode animationPlayMode)
{
	if (this->spriterAnimation == nullptr)
	{
		return;
	}

	this->clearPlayModeCompletion();

	const int completionToken = ++this->playModeCompletionToken;
	this->spriterAnimation->setAnimationLoopCompletionCallback([=]()
	{
		if (this->playModeCompletionToken != completionToken)
		{
			return;
		}

		// This one-shot completion callback has fired; future play requests
		// must be allowed to schedule a new completion even for same mode/name.
		std::function<void()> completionCallback = this->activePlayModeCallback;
		this->hasActivePlayMode = false;
		this->activePlayModeCallback = nullptr;

		switch (animationPlayMode)
		{
			case AnimationPlayMode::ReturnToIdle:
			{
				this->clearAnimationPriority();
				this->playAnimation(AnimationPlayMode::ReturnToIdle);
				break;
			}
			case AnimationPlayMode::PauseOnAnimationComplete:
			{
				this->spriterAnimation->setAnimationPaused(true);
				break;
			}
			case AnimationPlayMode::Callback:
			{
				if (completionCallback != nullptr)
				{
					completionCallback();
				}
				break;
			}
			default:
			case AnimationPlayMode::Repeat:
			{
				// Spriter timeline playback naturally wraps. Keep repeat mode active
				// without forcing explicit replays every cycle.
				break;
			}
		}
	});
}

void SmartAnimationNode::clearPlayModeCompletion()
{
	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->clearAnimationLoopCompletionCallback();
	}

	this->hasActivePlayMode = false;
	this->activePlayModeCallback = nullptr;
}
