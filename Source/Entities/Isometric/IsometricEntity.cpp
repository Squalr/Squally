#include "IsometricEntity.h"

IsometricEntity::IsometricEntity(ValueMap* initProperties, std::string scmlResource, float scale) : HackableObject(initProperties)
{
	// TODO: Configurable/randomizable start direction (if any)
	this->movement = Vec2(0.0f, 0.0f);

	this->size = size;

	this->animationNode = AnimationNode::create(scmlResource);
	this->animationNode->setScale(scale);

	this->animationNodeEntity = this->animationNode->play("Entity");
	this->animationNodeEntity->setCurrentAnimation("IdleNE");

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

	const float MOVE_SPEED = 256.0f;

	if (this->movement != Vec2::ZERO)
	{
		// Le isometric magic
		this->movement.x *= 2.0f;

		// TODO: I didnt even check this code and it's bad, but at least the animations kinda change
		if (abs(this->movement.x) >= abs(this->movement.y))
		{
			if (this->movement.x < 0.0f)
			{;
				this->animationNodeEntity->setCurrentAnimation("IdleNW");
			}
			else
			{
				this->animationNodeEntity->setCurrentAnimation("IdleNE");
			}
		}
		else
		{
			if (this->movement.y < 0.0f)
			{
				this->animationNodeEntity->setCurrentAnimation("IdleSW");
			}
			else
			{
				this->animationNodeEntity->setCurrentAnimation("IdleSE");
			}
		}

		this->setPosition(this->getPosition() + dt * this->movement * MOVE_SPEED);
	}
}
