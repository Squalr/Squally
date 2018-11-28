#include "Aster.h"

const std::string Aster::MapKeyNpcAster = "aster";

Aster* Aster::deserialize(ValueMap* initProperties)
{
	Aster* instance = new Aster(initProperties);

	instance->autorelease();

	return instance;
}

Aster::Aster(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Snow_Npcs_Aster_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Aster::~Aster()
{
}
