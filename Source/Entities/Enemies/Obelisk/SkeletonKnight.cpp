#include "SkeletonKnight.h"

SkeletonKnight* SkeletonKnight::create()
{
	SkeletonKnight* instance = new SkeletonKnight();

	instance->autorelease();

	return instance;
}

SkeletonKnight::SkeletonKnight() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_SkeletonKnight_Animations,
	false)
{
}

SkeletonKnight::~SkeletonKnight()
{
}
