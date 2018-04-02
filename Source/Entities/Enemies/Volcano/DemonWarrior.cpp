#include "DemonWarrior.h"

DemonWarrior* DemonWarrior::create()
{
	DemonWarrior* instance = new DemonWarrior();

	instance->autorelease();

	return instance;
}

DemonWarrior::DemonWarrior() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

DemonWarrior::~DemonWarrior()
{
}
