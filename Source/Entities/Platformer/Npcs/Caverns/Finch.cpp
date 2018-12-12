#include "Finch.h"

const std::string Finch::MapKeyNpcFinch = "finch";

Finch* Finch::deserialize(ValueMap* initProperties)
{
	Finch* instance = new Finch(initProperties);

	instance->autorelease();

	return instance;
}

Finch::Finch(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Caverns_Npcs_Finch_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Finch::~Finch()
{
}
