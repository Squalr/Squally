#include "EntityProjectileTargetBehavior.h"

#include "cocos/2d/CCDrawNode.h"

#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityProjectileTargetBehavior::MapKeyAttachedBehavior = "entity-projectile-target";

EntityProjectileTargetBehavior* EntityProjectileTargetBehavior::create(GameObject* owner)
{
	EntityProjectileTargetBehavior* instance = new EntityProjectileTargetBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityProjectileTargetBehavior::EntityProjectileTargetBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->projectileTarget = DrawNode::create();

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->projectileTarget->drawSolidCircle(Vec2::ZERO, 6.0f, 0.0f, 8, Color4F::ORANGE);

	this->addChild(this->projectileTarget);
}

EntityProjectileTargetBehavior::~EntityProjectileTargetBehavior()
{
}

void EntityProjectileTargetBehavior::onDeveloperModeEnable()
{
	super::onDeveloperModeEnable();

	this->projectileTarget->setVisible(true);
}

void EntityProjectileTargetBehavior::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	this->projectileTarget->setVisible(false);
}

void EntityProjectileTargetBehavior::onLoad()
{
}

void EntityProjectileTargetBehavior::initializePositions()
{
	super::initializePositions();

	if (this->entity != nullptr)
	{
		Vec2 collisionOffset = this->entity->getCollisionOffset();

		if (this->entity->isFlippedY())
		{
			Vec2 offset = Vec2(collisionOffset.x, -collisionOffset.y) - Vec2(0.0f, this->entity->getMovementSize().height / 2.0f);
			this->projectileTarget->setPosition(offset);
		}
		else
		{
			Vec2 offset = collisionOffset + Vec2(0.0f, this->entity->getMovementSize().height / 2.0f);
			this->projectileTarget->setPosition(offset);
		}
	}
}

cocos2d::Node* EntityProjectileTargetBehavior::getTarget()
{
	return this->projectileTarget;
}
