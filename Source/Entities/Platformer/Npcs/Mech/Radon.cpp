#include "Radon.h"

const std::string Radon::MapKeyNpcRadon = "radon";

Radon* Radon::deserialize(ValueMap* initProperties)
{
	Radon* instance = new Radon(initProperties);

	instance->autorelease();

	return instance;
}

Radon::Radon(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Mech_Npcs_Radon_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Radon::~Radon()
{
}
