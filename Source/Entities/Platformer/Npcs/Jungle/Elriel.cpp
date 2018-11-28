#include "Elriel.h"

const std::string Elriel::MapKeyNpcElriel = "elriel";

Elriel* Elriel::deserialize(ValueMap* initProperties)
{
	Elriel* instance = new Elriel(initProperties);

	instance->autorelease();

	return instance;
}

Elriel::Elriel(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Jungle_Npcs_Elriel_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Elriel::~Elriel()
{
}
