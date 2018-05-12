#include "SkeletonNecromancer.h"

SkeletonNecromancer* SkeletonNecromancer::create()
{
	SkeletonNecromancer* instance = new SkeletonNecromancer();

	instance->autorelease();

	return instance;
}

SkeletonNecromancer::SkeletonNecromancer() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_SkeletonNecromancer_Animations,
	false,
	Size(128.0f, 228.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletonNecromancer::~SkeletonNecromancer()
{
}
