#include "SkeletonBaron.h"

SkeletonBaron* SkeletonBaron::create()
{
	SkeletonBaron* instance = new SkeletonBaron();

	instance->autorelease();

	return instance;
}

SkeletonBaron::SkeletonBaron() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

SkeletonBaron::~SkeletonBaron()
{
}
