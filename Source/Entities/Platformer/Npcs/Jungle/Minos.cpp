#include "Minos.h"

const std::string Minos::MapKeyNpcMinos = "minos";

Minos* Minos::deserialize(ValueMap* initProperties)
{
	Minos* instance = new Minos(initProperties);

	instance->autorelease();

	return instance;
}

Minos::Minos(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_Npcs_Minos_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Minos::~Minos()
{
}
