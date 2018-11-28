#include "Sarude.h"

const std::string Sarude::MapKeyNpcSarude = "sarude";

Sarude* Sarude::deserialize(ValueMap* initProperties)
{
	Sarude* instance = new Sarude(initProperties);

	instance->autorelease();

	return instance;
}

Sarude::Sarude(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Caverns_Npcs_Sarude_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Sarude::~Sarude()
{
}
