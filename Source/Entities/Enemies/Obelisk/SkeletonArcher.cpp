#include "SkeletonArcher.h"

SkeletonArcher* SkeletonArcher::create()
{
	SkeletonArcher* instance = new SkeletonArcher();

	instance->autorelease();

	return instance;
}

SkeletonArcher::SkeletonArcher() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

SkeletonArcher::~SkeletonArcher()
{
}
