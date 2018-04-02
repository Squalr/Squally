#include "SkeletonMage.h"

SkeletonMage* SkeletonMage::create()
{
	SkeletonMage* instance = new SkeletonMage();

	instance->autorelease();

	return instance;
}

SkeletonMage::SkeletonMage() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

SkeletonMage::~SkeletonMage()
{
}
