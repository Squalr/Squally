#include "Mildred.h"

const std::string Mildred::MapKeyNpcMildred = "mildred";

Mildred* Mildred::deserialize(ValueMap* initProperties)
{
	Mildred* instance = new Mildred(initProperties);

	instance->autorelease();

	return instance;
}

Mildred::Mildred(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Caverns_Npcs_Mildred_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Mildred::~Mildred()
{
}
