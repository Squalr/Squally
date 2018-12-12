#include "Merlin.h"

const std::string Merlin::MapKeyNpcMerlin = "merlin";

Merlin* Merlin::deserialize(ValueMap* initProperties)
{
	Merlin* instance = new Merlin(initProperties);

	instance->autorelease();

	return instance;
}

Merlin::Merlin(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Castle_Npcs_Merlin_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Merlin::~Merlin()
{
}
