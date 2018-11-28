#include "Hera.h"

const std::string Hera::MapKeyNpcHera = "hera";

Hera* Hera::deserialize(ValueMap* initProperties)
{
	Hera* instance = new Hera(initProperties);

	instance->autorelease();

	return instance;
}

Hera::Hera(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Ruins_Npcs_Hera_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Hera::~Hera()
{
}
