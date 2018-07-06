#include "SkeletonWarrior.h"

const std::string SkeletonWarrior::KeyEnemySkeletonWarrior = "skeleton_warrior";

SkeletonWarrior* SkeletonWarrior::deserialize(ValueMap* initProperties)
{
	SkeletonWarrior* instance = new SkeletonWarrior(initProperties);

	instance->autorelease();

	return instance;
}

SkeletonWarrior::SkeletonWarrior(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Caverns_SkeletonWarrior_Animations,
	false,
	Size(128.0f, 216.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletonWarrior::~SkeletonWarrior()
{
}
