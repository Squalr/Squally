#include "Athena.h"

const std::string Athena::MapKeyNpcAthena = "athena";

Athena* Athena::deserialize(ValueMap* initProperties)
{
	Athena* instance = new Athena(initProperties);

	instance->autorelease();

	return instance;
}

Athena::Athena(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Ruins_Npcs_Athena_Animations ,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Athena::~Athena()
{
}
