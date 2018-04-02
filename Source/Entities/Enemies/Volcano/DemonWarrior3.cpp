#include "DemonWarrior3.h"

DemonWarrior3* DemonWarrior3::create()
{
	DemonWarrior3* instance = new DemonWarrior3();

	instance->autorelease();

	return instance;
}

DemonWarrior3::DemonWarrior3() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

DemonWarrior3::~DemonWarrior3()
{
}
