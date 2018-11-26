#include "Geryon.h"

const std::string Geryon::MapKeyNpcGeryon = "geryon";

Geryon* Geryon::deserialize(ValueMap* initProperties)
{
	Geryon* instance = new Geryon(initProperties);

	instance->autorelease();

	return instance;
}

Geryon::Geryon(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Ruins_Npcs_Geryon_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Geryon::~Geryon()
{
}
