#include "SmartAnimationNode.h"

#include <spriter2dx/AnimationNode.h>

#include "Engine/Animations/AnimationPart.h"

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
	this->animationNode = AnimationNode::create(animationResource);
	this->entity = this->animationNode->play(entityName);
	this->animationParts = std::map<std::string, AnimationPart*>();
	this->initialized = false;
	this->currentAnimation = "";

	this->addChild(this->animationNode);
}

SmartAnimationNode::~SmartAnimationNode()
{
}

void SmartAnimationNode::playAnimation(AnimationPlayMode animationPlayMode, float priority, float blendTime, std::function<void()> callback)
{
	this->playAnimation(SmartAnimationNode::DefaultAnimationName, animationPlayMode, priority, blendTime, callback);
}

void SmartAnimationNode::playAnimation(const char* animationName, AnimationPlayMode animationPlayMode, float priority, float blendTime, std::function<void()> callback)
{
	this->playAnimation(std::string(animationName), animationPlayMode, priority, blendTime, callback);
}

void SmartAnimationNode::playAnimation(std::string animationName, AnimationPlayMode animationPlayMode, float priority, float blendTime, std::function<void()> callback)
{
	if (this->entity == nullptr)
	{
		return;
	}

	if (priority <= this->currentAnimationPriority)
	{
		return;
	}

	this->currentAnimationPriority = priority;
	
	if (this->entity->hasAnimation(animationName))
	{
		if (!this->initialized || this->entity->currentAnimationName() != animationName)
		{
			this->initialized = true;
			this->entity->setCurrentTime(0.0f);
			this->entity->setCurrentAnimation(animationName, blendTime);
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

	AnimationPart* animationPart = AnimationPart::create(this->entity, partName);

	this->animationParts[partName] = animationPart;

	this->addChild(animationPart);

	return animationPart;
}

void SmartAnimationNode::restoreAnimationPart(std::string partName)
{
	auto animVariable = this->entity->getObjectInstance(partName);

	if (animVariable != nullptr)
	{
		animVariable->toggleTimelineCanUpdate(true);
	}
}

void SmartAnimationNode::setFlippedX(bool flippedX)
{
	this->animationNode->setFlippedX(flippedX);
}

void SmartAnimationNode::setFlippedY(bool flippedY)
{
	this->animationNode->setFlippedY(flippedY);
}

bool SmartAnimationNode::getFlippedX()
{
	return this->animationNode->getFlippedX();
}

bool SmartAnimationNode::getFlippedY()
{
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
	this->animationNode->disableRender();
}

void SmartAnimationNode::enableRender()
{
	this->animationNode->enableRender();
}
