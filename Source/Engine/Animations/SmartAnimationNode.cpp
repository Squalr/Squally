#include "SmartAnimationNode.h"

#include "SpriterPlusPlus/CCAnimationNode.h"

#include "Engine/Animations/AnimationPart.h"

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
	this->animationNode = AnimationNode::create(animationResource);
	this->entity = this->animationNode->play(entityName);
	this->cachedAnimationParts = std::map<std::string, AnimationPart*>();

	this->addChild(this->animationNode);
}

SmartAnimationNode::~SmartAnimationNode()
{
}

void SmartAnimationNode::playAnimation(bool repeat, float blendTime)
{
	this->playAnimation(SmartAnimationNode::DefaultAnimationName, repeat, blendTime);
}

void SmartAnimationNode::playAnimation(const char* animationName, bool repeat, float blendTime)
{
	this->playAnimation(std::string(animationName), repeat, blendTime);
}

void SmartAnimationNode::playAnimation(std::string animationName, bool repeat, float blendTime)
{
	if (this->entity->hasAnimation(animationName))
	{
		this->entity->setCurrentTime(0.0f);
		this->entity->setCurrentAnimation(animationName, blendTime);

		// Repeating is the default in SpriterPlusPlus, we have to explicitly set a callback to play something else
		if (!repeat && animationName != SmartAnimationNode::DefaultAnimationName)
		{
			this->entity->setAnimationCompleteCallback([=]()
			{
				// Just return to idle
				this->playAnimation(false);
			});
		}
	}
}

AnimationPart* SmartAnimationNode::getAnimationPart(std::string partName)
{
	if (this->cachedAnimationParts.find(partName) != this->cachedAnimationParts.end())
	{
		return this->cachedAnimationParts[partName];
	}

	AnimationPart* animationPart = AnimationPart::create(this->entity, partName);

	this->cachedAnimationParts[partName] = animationPart;

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
