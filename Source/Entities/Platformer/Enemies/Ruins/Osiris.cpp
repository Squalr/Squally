#include "Osiris.h"

const std::string Osiris::MapKeyEnemyOsiris = "osiris";

Osiris* Osiris::deserialize(ValueMap* initProperties)
{
	Osiris* instance = new Osiris(initProperties);

	instance->autorelease();

	return instance;
}

Osiris::Osiris(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Ruins_Enemies_Osiris_Animations,
	PlatformerCollisionType::Enemy,
	Size(324.0f, 316.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Osiris::~Osiris()
{
}
