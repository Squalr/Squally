#include "QueenElise.h"

const std::string QueenElise::MapKeyNpcQueenElise = "queen_elise";

QueenElise* QueenElise::deserialize(ValueMap* initProperties)
{
	QueenElise* instance = new QueenElise(initProperties);

	instance->autorelease();

	return instance;
}

QueenElise::QueenElise(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Mech_Npcs_QueenElise_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

QueenElise::~QueenElise()
{
}
