#include "SkeletonGhost.h"

SkeletonGhost* SkeletonGhost::create()
{
	SkeletonGhost* instance = new SkeletonGhost();

	instance->autorelease();

	return instance;
}

SkeletonGhost::SkeletonGhost() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

SkeletonGhost::~SkeletonGhost()
{
}
