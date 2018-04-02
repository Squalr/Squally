#include "TigerWarrior.h"

TigerWarrior* TigerWarrior::create()
{
	TigerWarrior* instance = new TigerWarrior();

	instance->autorelease();

	return instance;
}

TigerWarrior::TigerWarrior() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

TigerWarrior::~TigerWarrior()
{
}
