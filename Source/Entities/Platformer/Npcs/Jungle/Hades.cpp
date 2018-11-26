#include "Hades.h"

const std::string Hades::MapKeyNpcHades = "hades";

Hades* Hades::deserialize(ValueMap* initProperties)
{
	Hades* instance = new Hades(initProperties);

	instance->autorelease();

	return instance;
}

Hades::Hades(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Jungle_Npcs_Hades_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Hades::~Hades()
{
}
