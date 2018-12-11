#include "Dudly.h"

const std::string Dudly::MapKeyNpcDudly = "dudly";

Dudly* Dudly::deserialize(ValueMap* initProperties)
{
	Dudly* instance = new Dudly(initProperties);

	instance->autorelease();

	return instance;
}

Dudly::Dudly(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Forest_Npcs_Dudly_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Dudly::~Dudly()
{
}
