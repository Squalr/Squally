#include "SkeletonBaron.h"

const std::string SkeletonBaron::KeyEnemySkeletonBaron = "skeleton_baron";

SkeletonBaron* SkeletonBaron::deserialize(ValueMap* initProperties)
{
	SkeletonBaron* instance = new SkeletonBaron(initProperties);

	instance->autorelease();

	return instance;
}

SkeletonBaron::SkeletonBaron(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Obelisk_SkeletonBaron_Animations,
	false,
	Size(472.0f, 368.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletonBaron::~SkeletonBaron()
{
}
