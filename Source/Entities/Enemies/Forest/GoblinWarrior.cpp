#include "GoblinWarrior.h"

GoblinWarrior* GoblinWarrior::create()
{
	GoblinWarrior* instance = new GoblinWarrior();

	instance->autorelease();

	return instance;
}

GoblinWarrior::GoblinWarrior() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

GoblinWarrior::~GoblinWarrior()
{
}
