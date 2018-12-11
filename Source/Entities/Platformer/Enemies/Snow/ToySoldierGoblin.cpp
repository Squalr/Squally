#include "ToySoldierGoblin.h"

const std::string ToySoldierGoblin::MapKeyEnemyToySoldierGoblin = "toy_soldier_goblin";

ToySoldierGoblin* ToySoldierGoblin::deserialize(ValueMap* initProperties)
{
	ToySoldierGoblin* instance = new ToySoldierGoblin(initProperties);

	instance->autorelease();

	return instance;
}

ToySoldierGoblin::ToySoldierGoblin(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Snow_Enemies_ToySoldierGoblin_Animations,
	PlatformerCollisionType::Enemy,
	Size(112.0f, 288.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

ToySoldierGoblin::~ToySoldierGoblin()
{
}
