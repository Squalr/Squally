#include "OrcWarrior.h"

OrcWarrior* OrcWarrior::create()
{
	OrcWarrior* instance = new OrcWarrior();

	instance->autorelease();

	return instance;
}

OrcWarrior::OrcWarrior() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

OrcWarrior::~OrcWarrior()
{
}
