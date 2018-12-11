#include "Troll.h"

const std::string Troll::MapKeyEnemyTroll = "troll";

Troll* Troll::deserialize(ValueMap* initProperties)
{
	Troll* instance = new Troll(initProperties);

	instance->autorelease();

	return instance;
}

Troll::Troll(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Forest_Enemies_Troll_Animations,
	PlatformerCollisionType::Enemy,
	Size(256.0f, 248.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Troll::~Troll()
{
}
