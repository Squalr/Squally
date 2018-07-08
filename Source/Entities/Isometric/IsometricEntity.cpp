#include "IsometricEntity.h"

IsometricEntity::IsometricEntity(ValueMap* initProperties, std::string scmlResource, float scale) : HackableObject(initProperties)
{
	// TODO: Configurable/randomizable start direction (if any)
	this->movement = Vec2(0.0f, 0.0f);

	this->size = size;

	this->animationNode = AnimationNode::create(scmlResource);
	this->animationNode->setScale(scale);

	SpriterEngine::EntityInstance* entity = this->animationNode->play("Entity");
	entity->setCurrentAnimation("IdleNE");

	// Update width to be serialized
	if (this->properties != nullptr)
	{
		(*this->properties)[IsometricEntity::KeyWidth] = size.width * scale;
		(*this->properties)[IsometricEntity::KeyHeight] = size.height * scale;
	}

	this->addChild(this->animationNode);
}

IsometricEntity::~IsometricEntity()
{
}

void IsometricEntity::onEnter()
{
	HackableObject::onEnter();

	this->scheduleUpdate();
}

void IsometricEntity::update(float dt)
{
	HackableObject::update(dt);
}
