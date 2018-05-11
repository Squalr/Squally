#include "SkeletonNecromancer.h"

SkeletonNecromancer* SkeletonNecromancer::create()
{
	SkeletonNecromancer* instance = new SkeletonNecromancer();

	instance->autorelease();

	return instance;
}

SkeletonNecromancer::SkeletonNecromancer() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_SkeletonNecromancer_Animations,
	false)
{
}

SkeletonNecromancer::~SkeletonNecromancer()
{
}
