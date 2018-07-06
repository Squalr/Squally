#include "ToySoldierGoblin.h"

const std::string ToySoldierGoblin::KeyEnemyToySoldierGoblin = "toy_soldier_goblin";

ToySoldierGoblin* ToySoldierGoblin::deserialize(ValueMap* initProperties)
{
	ToySoldierGoblin* instance = new ToySoldierGoblin(initProperties);

	instance->autorelease();

	return instance;
}

ToySoldierGoblin::ToySoldierGoblin(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Snow_ToySoldierGoblin_Animations,
	false,
	Size(112.0f, 288.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

ToySoldierGoblin::~ToySoldierGoblin()
{
}
