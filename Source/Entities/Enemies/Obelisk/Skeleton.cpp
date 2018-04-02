#include "Skeleton.h"

Skeleton* Skeleton::create()
{
	Skeleton* instance = new Skeleton();

	instance->autorelease();

	return instance;
}

Skeleton::Skeleton() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Skeleton::~Skeleton()
{
}
