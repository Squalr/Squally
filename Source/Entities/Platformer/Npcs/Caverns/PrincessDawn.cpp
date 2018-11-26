#include "PrincessDawn.h"

const std::string PrincessDawn::MapKeyNpcPrincessDawn = "princess_dawn";

PrincessDawn* PrincessDawn::deserialize(ValueMap* initProperties)
{
	PrincessDawn* instance = new PrincessDawn(initProperties);

	instance->autorelease();

	return instance;
}

PrincessDawn::PrincessDawn(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Caverns_Npcs_PrincessDawn_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

PrincessDawn::~PrincessDawn()
{
}
