#include "TigerWarrior.h"

TigerWarrior* TigerWarrior::create()
{
	TigerWarrior* instance = new TigerWarrior();

	instance->autorelease();

	return instance;
}

TigerWarrior::TigerWarrior() : Entity::Entity()
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 4000.0f;

	this->movement.x = -1.0f;
	this->movement.y = 0.0f;

	this->spriteNode = Node::create();
	this->sprite = Sprite::create(Resources::Entities_Environment_Castle_Harpy_Idle_0001);
	this->walkAnimation = Animation::create();
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Entities_Environment_Castle_Harpy_Walk_0001);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Entities_Environment_Castle_Harpy_Walk_0002);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Entities_Environment_Castle_Harpy_Walk_0003);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Entities_Environment_Castle_Harpy_Walk_0004);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Entities_Environment_Castle_Harpy_Walk_0005);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Entities_Environment_Castle_Harpy_Walk_0006);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Entities_Environment_Castle_Harpy_Walk_0007);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Entities_Environment_Castle_Harpy_Walk_0008);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Entities_Environment_Castle_Harpy_Walk_0009);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Entities_Environment_Castle_Harpy_Walk_0010);
	this->walkAnimation->setDelayPerUnit(0.1f);
	this->sprite->runAction(RepeatForever::create(Sequence::create(Animate::create(this->walkAnimation), nullptr)));

	this->init(PhysicsBody::createBox(this->sprite->getContentSize()), CategoryGroup::G_EnemyFlying, true, false);

	this->spriteNode->addChild(this->sprite);
	this->addChild(this->spriteNode);
}

TigerWarrior::~TigerWarrior()
{
}

void TigerWarrior::update(float dt)
{
	Entity::update(dt);

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

bool TigerWarrior::contactBegin(CollisionData data)
{
	return false;
}

bool TigerWarrior::contactUpdate(CollisionData data)
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

bool TigerWarrior::contactEnd(CollisionData data)
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
