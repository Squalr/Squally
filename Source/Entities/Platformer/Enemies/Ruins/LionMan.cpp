#include "LionMan.h"

const std::string LionMan::MapKeyEnemyLionMan = "lion_man";

LionMan* LionMan::deserialize(ValueMap* initProperties)
{
	LionMan* instance = new LionMan(initProperties);

	instance->autorelease();

	return instance;
}

LionMan::LionMan(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Ruins_Enemies_LionMan_Animations,
	PlatformerCollisionType::Enemy,
	Size(256.0f, 326.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

LionMan::~LionMan()
{
}
