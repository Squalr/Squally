#include "Raven.h"

const std::string Raven::MapKeyNpcRaven = "raven";

Raven* Raven::deserialize(ValueMap* initProperties)
{
	Raven* instance = new Raven(initProperties);

	instance->autorelease();

	return instance;
}

Raven::Raven(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Castle_Npcs_Raven_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Raven::~Raven()
{
}
