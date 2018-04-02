#include "TigerWarrior2.h"

TigerWarrior2* TigerWarrior2::create()
{
	TigerWarrior2* instance = new TigerWarrior2();

	instance->autorelease();

	return instance;
}

TigerWarrior2::TigerWarrior2() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

TigerWarrior2::~TigerWarrior2()
{
}
