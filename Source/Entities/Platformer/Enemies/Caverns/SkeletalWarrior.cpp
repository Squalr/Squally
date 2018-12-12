#include "SkeletalWarrior.h"

const std::string SkeletalWarrior::MapKeyEnemySkeletalWarrior = "skeletal_warrior";

SkeletalWarrior* SkeletalWarrior::deserialize(ValueMap* initProperties)
{
	SkeletalWarrior* instance = new SkeletalWarrior(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalWarrior::SkeletalWarrior(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Caverns_Enemies_SkeletalWarrior_Animations,
	PlatformerCollisionType::Enemy,
	Size(128.0f, 216.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalWarrior::~SkeletalWarrior()
{
}
