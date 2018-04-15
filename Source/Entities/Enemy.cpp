#include "Enemy.h"

Enemy::Enemy(std::string scmlResource, std::string entityName, bool isFlying) : Entity::Entity()
{
	this->spriteNode = Node::create();
	this->animationNode = AnimationNode::create(scmlResource);
	this->animationNode->setScale(0.5f);

	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 4000.0f;

	// TODO: Configurable/randomizable start direction (if any)
	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	SpriterEngine::EntityInstance* entity = this->animationNode->play(entityName);
	entity->setCurrentAnimation("Idle");

	CategoryGroup categoryGroup = isFlying ? CategoryGroup::G_EnemyFlying : CategoryGroup::G_Enemy;

	// TODO: Size configurable
	this->init(PhysicsBody::createBox(Size(196.0f, 256.0f)), categoryGroup, true, false);

	this->spriteNode->addChild(this->animationNode);
	this->addChild(this->spriteNode);
}

Enemy::~Enemy()
{
}

void Enemy::update(float dt)
{
	Entity::update(dt);

	if (this->animationNode == nullptr || this->spriteNode == nullptr)
	{
		return;
	}

	this->movement.y = 0.0f;

	if (this->movement.x < 0.0f)
	{
		this->animationNode->setFlippedX(true);
	}
	else
	{
		this->animationNode->setFlippedX(false);
	}
}

bool Enemy::contactBegin(CollisionData data)
{
	return false;
}

bool Enemy::contactUpdate(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
	case CategoryGroup::G_Solid:
		switch (data.direction)
		{
		case CollisionDirection::Down:
			this->isOnGround = true;
			break;
		case CollisionDirection::Left:
			this->movement.x = 1.0f;
			break;
		case CollisionDirection::Right:
			this->movement.x = -1.0f;
			break;
		case CollisionDirection::StepLeft:
		case CollisionDirection::StepRight:
			this->movement.y = 0.5f;
			break;
		}
		return true;
	}

	return false;
}

bool Enemy::contactEnd(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_Solid:
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
		this->isOnGround = false;
		return true;
	}

	return false;
}
