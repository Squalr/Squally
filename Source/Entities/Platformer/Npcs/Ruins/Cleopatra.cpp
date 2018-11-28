#include "Cleopatra.h"

const std::string Cleopatra::MapKeyNpcCleopatra = "cleopatra";

Cleopatra* Cleopatra::deserialize(ValueMap* initProperties)
{
	Cleopatra* instance = new Cleopatra(initProperties);

	instance->autorelease();

	return instance;
}

Cleopatra::Cleopatra(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Ruins_Npcs_Cleopatra_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Cleopatra::~Cleopatra()
{
}
