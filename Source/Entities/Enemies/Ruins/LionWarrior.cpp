#include "LionWarrior.h"

LionWarrior* LionWarrior::create()
{
	LionWarrior* instance = new LionWarrior();

	instance->autorelease();

	return instance;
}

LionWarrior::LionWarrior() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

LionWarrior::~LionWarrior()
{
}
