#include "Enemy.h"

Enemy::Enemy() : Entity::Entity()
{
	this->sprite = nullptr;
	this->spriteNode = nullptr;

	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 4000.0f;

	this->movement.x = -1.0f;
	this->movement.y = 0.0f;

}

Enemy::~Enemy()
{
}

void Enemy::initializeEnemy(std::string baseIdleResource, float idleFrameSpeed, std::string baseWalkResource, float walkFrameSpeed, bool isFlying)
{
	this->spriteNode = Node::create();
	this->sprite = Sprite::create(baseIdleResource);
	this->idleAnimation = Animation::create();
	this->walkAnimation = Animation::create();

	CategoryGroup categoryGroup = isFlying ? CategoryGroup::G_EnemyFlying : CategoryGroup::G_Enemy;
	std::vector<std::string> idleAnimationResources = GameUtils::getAllAnimationFiles(baseIdleResource);
	std::vector<std::string> walkAnimationResources = GameUtils::getAllAnimationFiles(baseWalkResource);

	for (auto it = idleAnimationResources.begin(); it != idleAnimationResources.end(); it++)
	{
		this->idleAnimation->addSpriteFrameWithFileName(*it);
	}

	for (auto it = walkAnimationResources.begin(); it != walkAnimationResources.end(); it++)
	{
		this->walkAnimation->addSpriteFrameWithFileName(*it);
	}

	this->idleAnimation->setDelayPerUnit(idleFrameSpeed);
	this->walkAnimation->setDelayPerUnit(walkFrameSpeed);
	this->sprite->runAction(RepeatForever::create(Sequence::create(Animate::create(this->walkAnimation), nullptr)));
	this->init(PhysicsBody::createBox(this->sprite->getContentSize()), categoryGroup, true, false);

	this->spriteNode->addChild(this->sprite);
	this->addChild(this->spriteNode);
}

void Enemy::initializeEnemy2(std::string scmlResource, std::string idleAnimation, std::string walkAnimation, bool isFlying)
{
	this->spriteNode = Node::create();
	this->sprite = Sprite::create(Resources::EmptyImage);
	this->idleAnimation = Animation::create();
	this->walkAnimation = Animation::create();

	this->animationNode = AnimationNode::create(Resources::Entities_Environment_Lava_BossDemonKing_Animations);

	SpriterEngine::EntityInstance* entity = this->animationNode->play("BossDemonKing");
	entity->setCurrentAnimation("Idle");

	CategoryGroup categoryGroup = isFlying ? CategoryGroup::G_EnemyFlying : CategoryGroup::G_Enemy;

	this->sprite->runAction(RepeatForever::create(Sequence::create(Animate::create(this->walkAnimation), nullptr)));
	this->init(PhysicsBody::createBox(this->sprite->getContentSize()), categoryGroup, true, false);

	this->spriteNode->addChild(this->sprite);
	this->spriteNode->addChild(this->animationNode);
	this->addChild(this->spriteNode);
}

void Enemy::update(float dt)
{
	Entity::update(dt);

	if (sprite == nullptr || spriteNode == nullptr)
	{
		return;
	}

	this->movement.y = 0.0f;

	if (this->movement.x < 0.0f)
	{
		this->sprite->setFlippedX(true);
	}
	else
	{
		this->sprite->setFlippedX(false);
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
