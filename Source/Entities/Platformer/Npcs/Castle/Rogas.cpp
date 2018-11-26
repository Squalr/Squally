#include "Rogas.h"

const std::string Rogas::MapKeyNpcRogas = "rogas";

Rogas* Rogas::deserialize(ValueMap* initProperties)
{
	Rogas* instance = new Rogas(initProperties);

	instance->autorelease();

	return instance;
}

Rogas::Rogas(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Castle_Npcs_Rogas_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Rogas::~Rogas()
{
}
