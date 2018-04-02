#include "MedusaWarrior.h"

MedusaWarrior* MedusaWarrior::create()
{
	MedusaWarrior* instance = new MedusaWarrior();

	instance->autorelease();

	return instance;
}

MedusaWarrior::MedusaWarrior() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

MedusaWarrior::~MedusaWarrior()
{
}
