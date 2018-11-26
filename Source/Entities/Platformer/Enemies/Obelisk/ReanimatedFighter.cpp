#include "ReanimatedFighter.h"

const std::string ReanimatedFighter::MapKeyEnemyReanimatedFighter = "reanimated_fighter";

ReanimatedFighter* ReanimatedFighter::deserialize(ValueMap* initProperties)
{
	ReanimatedFighter* instance = new ReanimatedFighter(initProperties);

	instance->autorelease();

	return instance;
}

ReanimatedFighter::ReanimatedFighter(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Obelisk_Enemies_ReanimatedFighter_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(256.0f, 248.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

ReanimatedFighter::~ReanimatedFighter()
{
}
