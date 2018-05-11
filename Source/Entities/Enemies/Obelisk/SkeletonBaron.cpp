#include "SkeletonBaron.h"

SkeletonBaron* SkeletonBaron::create()
{
	SkeletonBaron* instance = new SkeletonBaron();

	instance->autorelease();

	return instance;
}

SkeletonBaron::SkeletonBaron() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_SkeletonBaron_Animations,
	false)
{
}

SkeletonBaron::~SkeletonBaron()
{
}
