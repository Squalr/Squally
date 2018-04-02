#include "SkeletonWarrior2.h"

SkeletonWarrior2* SkeletonWarrior2::create()
{
	SkeletonWarrior2* instance = new SkeletonWarrior2();

	instance->autorelease();

	return instance;
}

SkeletonWarrior2::SkeletonWarrior2() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

SkeletonWarrior2::~SkeletonWarrior2()
{
}
