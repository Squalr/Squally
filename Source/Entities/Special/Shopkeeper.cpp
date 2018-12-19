#include "Shopkeeper.h"

#include "Resources/EntityResources.h"

Shopkeeper* Shopkeeper::create()
{
	Shopkeeper* instance = new Shopkeeper();

	instance->autorelease();

	return instance;
}

Shopkeeper::Shopkeeper()
{
	this->animationNode = AnimationNode::create(EntityResources::Misc_Shopkeeper_Animations);

	SpriterEngine::EntityInstance* entity = this->animationNode->play("Entity");
	entity->setCurrentAnimation("Idle");

	this->addChild(this->animationNode);
}

Shopkeeper::~Shopkeeper()
{
}
