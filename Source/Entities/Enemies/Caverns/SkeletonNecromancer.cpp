#include "SkeletonNecromancer.h"

const std::string SkeletonNecromancer::KeyEnemySkeletonNecromancer = "skeleton_necromancer";

SkeletonNecromancer* SkeletonNecromancer::deserialize(ValueMap* initProperties)
{
	SkeletonNecromancer* instance = new SkeletonNecromancer(initProperties);

	instance->autorelease();

	return instance;
}

SkeletonNecromancer::SkeletonNecromancer(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Caverns_SkeletonNecromancer_Animations,
	false,
	Size(128.0f, 228.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletonNecromancer::~SkeletonNecromancer()
{
}
