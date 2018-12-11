#include "Gramps.h"

const std::string Gramps::MapKeyNpcGramps = "gramps";

Gramps* Gramps::deserialize(ValueMap* initProperties)
{
	Gramps* instance = new Gramps(initProperties);

	instance->autorelease();

	return instance;
}

Gramps::Gramps(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Jungle_Npcs_Gramps_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Gramps::~Gramps()
{
}
