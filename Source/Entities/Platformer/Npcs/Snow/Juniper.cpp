#include "Juniper.h"

const std::string Juniper::MapKeyNpcJuniper = "juniper";

Juniper* Juniper::deserialize(ValueMap* initProperties)
{
	Juniper* instance = new Juniper(initProperties);

	instance->autorelease();

	return instance;
}

Juniper::Juniper(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Snow_Npcs_Juniper_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Juniper::~Juniper()
{
}
