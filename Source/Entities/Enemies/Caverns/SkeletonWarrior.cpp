#include "SkeletonWarrior.h"

SkeletonWarrior* SkeletonWarrior::create()
{
	SkeletonWarrior* instance = new SkeletonWarrior();

	instance->autorelease();

	return instance;
}

SkeletonWarrior::SkeletonWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_SkeletonWarrior_Animations,
	false,
	Size(128.0f, 216.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletonWarrior::~SkeletonWarrior()
{
}
