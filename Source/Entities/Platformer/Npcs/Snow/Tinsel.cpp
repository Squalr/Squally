#include "Tinsel.h"

const std::string Tinsel::MapKeyNpcTinsel = "tinsel";

Tinsel* Tinsel::deserialize(ValueMap* initProperties)
{
	Tinsel* instance = new Tinsel(initProperties);

	instance->autorelease();

	return instance;
}

Tinsel::Tinsel(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Snow_Npcs_Tinsel_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Tinsel::~Tinsel()
{
}
