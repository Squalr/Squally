#include "SkeletalArcher.h"

const std::string SkeletalArcher::MapKeyEnemySkeletalArcher = "skeletal_archer";

SkeletalArcher* SkeletalArcher::deserialize(ValueMap* initProperties)
{
	SkeletalArcher* instance = new SkeletalArcher(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalArcher::SkeletalArcher(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Caverns_Enemies_SkeletalArcher_Animations,
	PlatformerCollisionType::Enemy,
	Size(128.0f, 216.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalArcher::~SkeletalArcher()
{
}
