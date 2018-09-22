#include "Knight.h"

const std::string Knight::KeyNpcKnight = "knight";

Knight* Knight::deserialize(ValueMap* initProperties)
{
	Knight* instance = new Knight(initProperties);

	instance->autorelease();

	return instance;
}

Knight::Knight(ValueMap* initProperties) : NpcBase::NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Volcano_Npcs_FireKnight_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeNpc,
	Size(96.0f, 128.0f),
	0.25f,
	Vec2(0.0f, -72.0f))
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 3000.0f;

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	this->initializeCardData();
}

Knight::~Knight()
{
	this->deck->release();
}

void Knight::initializeCardData()
{
}

void Knight::update(float dt)
{
	NpcBase::update(dt);
}
