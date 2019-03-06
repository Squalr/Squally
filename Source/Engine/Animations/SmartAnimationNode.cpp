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
	this->animationNode = AnimationNode::create(animationResource);
	this->entity = this->animationNode->play(entityName);
	this->animationParts = std::map<std::string, AnimationPart*>();

	this->addChild(this->animationNode);
}

SmartAnimationNode::~SmartAnimationNode()
{
}

void SmartAnimationNode::playAnimation(AnimationPlayMode animationPlayMode, float blendTime)
{
	this->playAnimation(SmartAnimationNode::DefaultAnimationName, animationPlayMode, blendTime);
}

void SmartAnimationNode::playAnimation(const char* animationName, AnimationPlayMode animationPlayMode, float blendTime)
{
	this->playAnimation(std::string(animationName), animationPlayMode, blendTime);
}

void SmartAnimationNode::playAnimation(std::string animationName, AnimationPlayMode animationPlayMode, float blendTime)
{
	if (this->entity->hasAnimation(animationName))
	{
		// if (this->entity->currentAnimationName() != animationName)
		{
			this->entity->setCurrentTime(0.0f);
			this->entity->setCurrentAnimation(animationName, blendTime);
		}

		switch (animationPlayMode)
		{
			case AnimationPlayMode::ReturnToIdle:
			{
				this->entity->setAnimationCompleteCallback([=]()
				{
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
			default:
			case AnimationPlayMode::Repeat:
			{
				// Repeating is the default behavior for Spriter
				break;
			}
		}
	}
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
