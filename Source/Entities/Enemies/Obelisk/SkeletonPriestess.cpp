#include "SkeletonPriestess.h"

SkeletonPriestess* SkeletonPriestess::create()
{
	SkeletonPriestess* instance = new SkeletonPriestess();

	instance->autorelease();

	return instance;
}

SkeletonPriestess::SkeletonPriestess() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

SkeletonPriestess::~SkeletonPriestess()
{
}
