#include "Ursula.h"

const std::string Ursula::MapKeyNpcUrsula = "ursula";

Ursula* Ursula::deserialize(ValueMap* initProperties)
{
	Ursula* instance = new Ursula(initProperties);

	instance->autorelease();

	return instance;
}

Ursula::Ursula(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Obelisk_Npcs_Ursula_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Ursula::~Ursula()
{
}
