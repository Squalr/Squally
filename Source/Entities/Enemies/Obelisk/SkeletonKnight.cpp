#include "SkeletonKnight.h"

const std::string SkeletonKnight::KeyEnemySkeletonKnight = "skeleton_knight";

SkeletonKnight* SkeletonKnight::create()
{
	SkeletonKnight* instance = new SkeletonKnight();

	instance->autorelease();

	return instance;
}

SkeletonKnight::SkeletonKnight() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_SkeletonKnight_Animations,
	false,
	Size(212.0f, 280.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletonKnight::~SkeletonKnight()
{
}
