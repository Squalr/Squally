#include "Lucifer.h"

const std::string Lucifer::MapKeyNpcLucifer = "lucifer";

Lucifer* Lucifer::deserialize(ValueMap* initProperties)
{
	Lucifer* instance = new Lucifer(initProperties);

	instance->autorelease();

	return instance;
}

Lucifer::Lucifer(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Volcano_Npcs_Lucifer_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Lucifer::~Lucifer()
{
}
