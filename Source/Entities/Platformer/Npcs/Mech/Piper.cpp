#include "Piper.h"

const std::string Piper::MapKeyNpcPiper = "piper";

Piper* Piper::deserialize(ValueMap* initProperties)
{
	Piper* instance = new Piper(initProperties);

	instance->autorelease();

	return instance;
}

Piper::Piper(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Mech_Npcs_Piper_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Piper::~Piper()
{
}
