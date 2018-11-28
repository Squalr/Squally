#include "Necron.h"

const std::string Necron::MapKeyNpcNecron = "necron";

Necron* Necron::deserialize(ValueMap* initProperties)
{
	Necron* instance = new Necron(initProperties);

	instance->autorelease();

	return instance;
}

Necron::Necron(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Obelisk_Npcs_Necron_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Necron::~Necron()
{
}
