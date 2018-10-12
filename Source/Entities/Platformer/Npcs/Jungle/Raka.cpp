#include "Raka.h"

const std::string Raka::MapKeyNpcRaka = "raka";

Raka* Raka::deserialize(ValueMap* initProperties)
{
	Raka* instance = new Raka(initProperties);

	instance->autorelease();

	return instance;
}

Raka::Raka(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_Npcs_Raka_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Raka::~Raka()
{
}
