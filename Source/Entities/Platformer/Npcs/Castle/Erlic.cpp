#include "Erlic.h"

const std::string Erlic::MapKeyNpcErlic = "erlic";

Erlic* Erlic::deserialize(ValueMap* initProperties)
{
	Erlic* instance = new Erlic(initProperties);

	instance->autorelease();

	return instance;
}

Erlic::Erlic(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Castle_Npcs_Elric_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Erlic::~Erlic()
{
}
