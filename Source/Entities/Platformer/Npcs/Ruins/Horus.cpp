#include "Horus.h"

const std::string Horus::MapKeyNpcHorus = "horus";

Horus* Horus::deserialize(ValueMap* initProperties)
{
	Horus* instance = new Horus(initProperties);

	instance->autorelease();

	return instance;
}

Horus::Horus(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Ruins_Npcs_Horus_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Horus::~Horus()
{
}
