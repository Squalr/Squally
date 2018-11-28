#include "Polyphemus.h"

const std::string Polyphemus::MapKeyNpcPolyphemus = "polyphemus";

Polyphemus* Polyphemus::deserialize(ValueMap* initProperties)
{
	Polyphemus* instance = new Polyphemus(initProperties);

	instance->autorelease();

	return instance;
}

Polyphemus::Polyphemus(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Forest_Npcs_Polyphemus_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Polyphemus::~Polyphemus()
{
}
