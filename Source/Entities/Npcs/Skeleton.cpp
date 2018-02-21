#include "Skeleton.h"

Skeleton* Skeleton::create()
{
	Skeleton* skeleton = new Skeleton();

	skeleton->autorelease();

	return skeleton;
}

Skeleton::Skeleton() : Entity::Entity()
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 3000.0f;

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	this->spriteNode = Node::create();
	this->skeletonSprite = Sprite::create(Resources::Ingame_Sprites_Snail_SnailWalking1);
	this->walkAnimation = Animation::create();
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Snail_SnailWalking1);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Snail_SnailWalking2);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Snail_SnailWalking3);
	this->walkAnimation->addSpriteFrameWithFileName(Resources::Ingame_Sprites_Snail_SnailWalking4);
	this->walkAnimation->setDelayPerUnit(0.15f);
	this->skeletonSprite->runAction(RepeatForever::create(Sequence::create(Animate::create(this->walkAnimation), nullptr)));

	this->init(PhysicsBody::createBox(this->skeletonSprite->getContentSize()), CategoryGroup::G_Npc, true, false);

	this->spriteNode->addChild(this->skeletonSprite);
	this->addChild(this->spriteNode);
}

Skeleton::~Skeleton()
{
}

void Skeleton::update(float dt)
{
	Entity::update(dt);

	this->movement.y = 0.0f;

	/*
	if (this->getRotation() < -15.0f)
	{
		this->setRotation(-15.0f);
	}
	else if (this->getRotation() > 15.0f)
	{
		this->setRotation(15.0f);
	}*/

	if (this->movement.x < 0.0f)
	{
		this->skeletonSprite->setFlippedX(true);
	}
	else
	{
		this->skeletonSprite->setFlippedX(false);
	}
}

bool Skeleton::contactBegin(CollisionData data)
{
	return false;
}

bool Skeleton::contactUpdate(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
	case CategoryGroup::G_Solid:
		if (abs(data.normal.y) >= Entity::normalJumpThreshold)
		{
			this->isOnGround = true;
		}

		switch (data.direction)
		{
		case CollisionDirection::Left:
			this->movement.x = 1.0f;
			break;
		case CollisionDirection::Right:
			this->movement.x = -1.0f;
			break;
		case CollisionDirection::StepLeft:
		case CollisionDirection::StepRight:
			this->movement.y = 0.35f;
			break;
		}
		return true;
	}

	return false;
}

bool Skeleton::contactEnd(CollisionData data)
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
