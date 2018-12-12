#include "Ash.h"

const std::string Ash::MapKeyNpcAsh = "ash";

Ash* Ash::deserialize(ValueMap* initProperties)
{
	Ash* instance = new Ash(initProperties);

	instance->autorelease();

	return instance;
}

Ash::Ash(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Volcano_Npcs_Ash_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Ash::~Ash()
{
}
