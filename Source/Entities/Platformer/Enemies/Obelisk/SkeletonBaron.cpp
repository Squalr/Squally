#include "SkeletonBaron.h"

const std::string SkeletonBaron::KeyEnemySkeletonBaron = "skeleton_baron";

SkeletonBaron* SkeletonBaron::deserialize(ValueMap* initProperties)
{
	SkeletonBaron* instance = new SkeletonBaron(initProperties);

	instance->autorelease();

	return instance;
}

SkeletonBaron::SkeletonBaron(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Obelisk_SkeletonBaron_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 368.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletonBaron::~SkeletonBaron()
{
}
