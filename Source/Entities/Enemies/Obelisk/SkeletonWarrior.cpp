#include "SkeletonWarrior.h"

SkeletonWarrior* SkeletonWarrior::create()
{
	SkeletonWarrior* instance = new SkeletonWarrior();

	instance->autorelease();

	return instance;
}

SkeletonWarrior::SkeletonWarrior() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

SkeletonWarrior::~SkeletonWarrior()
{
}
