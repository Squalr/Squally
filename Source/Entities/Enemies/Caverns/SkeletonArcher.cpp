#include "SkeletonArcher.h"

const std::string SkeletonArcher::KeyEnemySkeletonArcher = "skeleton_archer";

SkeletonArcher* SkeletonArcher::create()
{
	SkeletonArcher* instance = new SkeletonArcher();

	instance->autorelease();

	return instance;
}

SkeletonArcher::SkeletonArcher() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_SkeletonArcher_Animations,
	false,
	Size(128.0f, 216.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletonArcher::~SkeletonArcher()
{
}
