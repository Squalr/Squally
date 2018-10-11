#include "ReanimatedFighter.h"

const std::string ReanimatedFighter::KeyEnemyReanimatedFighter = "reanimated_fighter";

ReanimatedFighter* ReanimatedFighter::deserialize(ValueMap* initProperties)
{
	ReanimatedFighter* instance = new ReanimatedFighter(initProperties);

	instance->autorelease();

	return instance;
}

ReanimatedFighter::ReanimatedFighter(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Forest_Enemies_ReanimatedFighter_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(256.0f, 248.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

ReanimatedFighter::~ReanimatedFighter()
{
}
