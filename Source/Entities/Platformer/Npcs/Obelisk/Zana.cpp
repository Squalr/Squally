#include "Zana.h"

const std::string Zana::MapKeyNpcZana = "zana";

Zana* Zana::deserialize(ValueMap* initProperties)
{
	Zana* instance = new Zana(initProperties);

	instance->autorelease();

	return instance;
}

Zana::Zana(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Obelisk_Npcs_Zana_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Zana::~Zana()
{
}
