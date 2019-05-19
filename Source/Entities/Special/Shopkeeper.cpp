#include "Shopkeeper.h"

#include "Engine/Animations/SmartAnimationNode.h"

#include "Resources/EntityResources.h"

Shopkeeper* Shopkeeper::create()
{
	Shopkeeper* instance = new Shopkeeper();

	instance->autorelease();

	return instance;
}

Shopkeeper::Shopkeeper()
{
	this->animationNode = SmartAnimationNode::create(EntityResources::Misc_LambdaCrypts_Shopkeeper_Animations);

	this->animationNode->playAnimation(SmartAnimationNode::AnimationPlayMode::Repeat);

	this->addChild(this->animationNode);
}

Shopkeeper::~Shopkeeper()
{
}
