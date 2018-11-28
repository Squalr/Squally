#include "Kringle.h"

const std::string Kringle::MapKeyNpcKringle = "kringle";

Kringle* Kringle::deserialize(ValueMap* initProperties)
{
	Kringle* instance = new Kringle(initProperties);

	instance->autorelease();

	return instance;
}

Kringle::Kringle(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Snow_Npcs_Kringle_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Kringle::~Kringle()
{
}
