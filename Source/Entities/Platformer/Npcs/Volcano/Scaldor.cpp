#include "Scaldor.h"

const std::string Scaldor::MapKeyNpcScaldor = "scaldor";

Scaldor* Scaldor::deserialize(ValueMap* initProperties)
{
	Scaldor* instance = new Scaldor(initProperties);

	instance->autorelease();

	return instance;
}

Scaldor::Scaldor(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Volcano_Npcs_Scaldor_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Scaldor::~Scaldor()
{
}
