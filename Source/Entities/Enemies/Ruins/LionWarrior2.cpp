#include "LionWarrior2.h"

LionWarrior2* LionWarrior2::create()
{
	LionWarrior2* instance = new LionWarrior2();

	instance->autorelease();

	return instance;
}

LionWarrior2::LionWarrior2() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

LionWarrior2::~LionWarrior2()
{
}
