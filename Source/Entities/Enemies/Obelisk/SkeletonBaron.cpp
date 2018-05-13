#include "SkeletonBaron.h"

SkeletonBaron* SkeletonBaron::create()
{
	SkeletonBaron* instance = new SkeletonBaron();

	instance->autorelease();

	return instance;
}

SkeletonBaron::SkeletonBaron() : Enemy::Enemy(
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
