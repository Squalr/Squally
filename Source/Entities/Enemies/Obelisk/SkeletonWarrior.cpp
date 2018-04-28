#include "SkeletonWarrior.h"

SkeletonWarrior* SkeletonWarrior::create()
{
	SkeletonWarrior* instance = new SkeletonWarrior();

	instance->autorelease();

	return instance;
}

SkeletonWarrior::SkeletonWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

SkeletonWarrior::~SkeletonWarrior()
{
}
