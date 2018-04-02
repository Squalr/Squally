#include "SkeletonCleaver.h"

SkeletonCleaver* SkeletonCleaver::create()
{
	SkeletonCleaver* instance = new SkeletonCleaver();

	instance->autorelease();

	return instance;
}

SkeletonCleaver::SkeletonCleaver() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

SkeletonCleaver::~SkeletonCleaver()
{
}
