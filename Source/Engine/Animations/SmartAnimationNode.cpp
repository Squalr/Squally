#include "SmartAnimationNode.h"

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

	this->addChild(this->animationNode);
}

SmartAnimationNode::~SmartAnimationNode()
{
}

void SmartAnimationNode::playAnimation(float blendTime)
{
	this->entity->setCurrentTime(0.0f);
	this->entity->setCurrentAnimation(SmartAnimationNode::DefaultAnimationName, blendTime);
}

void SmartAnimationNode::playAnimation(std::string animationName, float blendTime)
{
	this->entity->setCurrentTime(0.0f);
	this->entity->setCurrentAnimation(animationName, blendTime);
}
