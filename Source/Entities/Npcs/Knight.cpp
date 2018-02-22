#include "Knight.h"

Knight* Knight::create()
{
	Knight* knight = new Knight();

	knight->autorelease();

	return knight;
}

Knight::Knight() : NpcBase::NpcBase()
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 3000.0f;

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	this->spriteNode = Node::create();
	this->knightSprite = Sprite::create(Resources::Ingame_Sprites_Knight_KnightStanding);

	this->init(PhysicsBody::createBox(this->knightSprite->getContentSize()), CategoryGroup::G_Npc, true, false);

	this->spriteNode->addChild(this->knightSprite);
	this->addChild(this->spriteNode);
}

Knight::~Knight()
{
}

void Knight::update(float dt)
{
	NpcBase::update(dt);
}
