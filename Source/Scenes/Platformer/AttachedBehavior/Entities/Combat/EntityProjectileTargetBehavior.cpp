#include "EntityProjectileTargetBehavior.h"

#include "cocos/2d/CCDrawNode.h"

#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityProjectileTargetBehavior::MapKey = "entity-projectile-target";

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

void EntityProjectileTargetBehavior::onDeveloperModeEnable(int debugLevel)
{
	super::onDeveloperModeEnable(debugLevel);

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

void EntityProjectileTargetBehavior::onDisable()
{
	super::onDisable();
}

void EntityProjectileTargetBehavior::initializePositions()
{
	super::initializePositions();

	if (this->entity != nullptr)
	{
		this->projectileTarget->setPosition(this->entity->getEntityCenterPoint());
	}
}

cocos2d::Node* EntityProjectileTargetBehavior::getTarget()
{
	return this->projectileTarget;
}
