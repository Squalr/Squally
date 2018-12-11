#include "Abomination.h"

const std::string Abomination::MapKeyEnemyAbomination = "abomination";

Abomination* Abomination::deserialize(ValueMap* initProperties)
{
	Abomination* instance = new Abomination(initProperties);

	instance->autorelease();

	return instance;
}

Abomination::Abomination(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Obelisk_Enemies_Abomination_Animations,
	PlatformerCollisionType::Enemy,
	Size(296.0f, 356.0f),
	0.6f,
	Vec2(0.0f, 0.0f))
{
}

Abomination::~Abomination()
{
}
