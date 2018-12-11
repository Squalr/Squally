#include "Toben.h"

const std::string Toben::MapKeyNpcToben = "toben";

Toben* Toben::deserialize(ValueMap* initProperties)
{
	Toben* instance = new Toben(initProperties);

	instance->autorelease();

	return instance;
}

Toben::Toben(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Forest_Npcs_Toben_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Toben::~Toben()
{
}
