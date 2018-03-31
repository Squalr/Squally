#include "Skeleton.h"

Skeleton* Skeleton::create()
{
	Skeleton* skeleton = new Skeleton();

	skeleton->autorelease();

	return skeleton;
}

Skeleton::Skeleton() : NpcBase::NpcBase()
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 3000.0f;

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	this->spriteNode = Node::create();
	this->skeletonSprite = Sprite::create(Resources::Entities_Environment_Ruins_SkeletalMage_attack__000);

	this->init(PhysicsBody::createBox(this->skeletonSprite->getContentSize()), CategoryGroup::G_Npc, true, false);

	this->spriteNode->addChild(this->skeletonSprite);
	this->addChild(this->spriteNode);
}

Skeleton::~Skeleton()
{
}

void Skeleton::update(float dt)
{
	NpcBase::update(dt);
}
