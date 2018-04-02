#include "AnubisWarrior.h"

AnubisWarrior* AnubisWarrior::create()
{
	AnubisWarrior* instance = new AnubisWarrior();

	instance->autorelease();

	return instance;
}

AnubisWarrior::AnubisWarrior() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

AnubisWarrior::~AnubisWarrior()
{
}
