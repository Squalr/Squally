#include "DemonWarrior2.h"

DemonWarrior2* DemonWarrior2::create()
{
	DemonWarrior2* instance = new DemonWarrior2();

	instance->autorelease();

	return instance;
}

DemonWarrior2::DemonWarrior2() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

DemonWarrior2::~DemonWarrior2()
{
}
