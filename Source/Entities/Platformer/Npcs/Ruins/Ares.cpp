#include "Ares.h"

const std::string Ares::MapKeyNpcAres = "ares";

Ares* Ares::deserialize(ValueMap* initProperties)
{
	Ares* instance = new Ares(initProperties);

	instance->autorelease();

	return instance;
}

Ares::Ares(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Ruins_Npcs_Ares_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Ares::~Ares()
{
}
