#include "Poseidon.h"

const std::string Poseidon::MapKeyNpcPoseidon = "poseidon";

Poseidon* Poseidon::deserialize(ValueMap* initProperties)
{
	Poseidon* instance = new Poseidon(initProperties);

	instance->autorelease();

	return instance;
}

Poseidon::Poseidon(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Ruins_Npcs_Poseidon_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Poseidon::~Poseidon()
{
}
