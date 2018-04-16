#include "SkeletonWarrior2.h"

SkeletonWarrior2* SkeletonWarrior2::create()
{
	SkeletonWarrior2* instance = new SkeletonWarrior2();

	instance->autorelease();

	return instance;
}

SkeletonWarrior2::SkeletonWarrior2() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

SkeletonWarrior2::~SkeletonWarrior2()
{
}
