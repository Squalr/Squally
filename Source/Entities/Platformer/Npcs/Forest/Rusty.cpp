#include "Rusty.h"

const std::string Rusty::MapKeyNpcRusty = "rusty";

Rusty* Rusty::deserialize(ValueMap* initProperties)
{
	Rusty* instance = new Rusty(initProperties);

	instance->autorelease();

	return instance;
}

Rusty::Rusty(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Forest_Npcs_Rusty_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Rusty::~Rusty()
{
}
