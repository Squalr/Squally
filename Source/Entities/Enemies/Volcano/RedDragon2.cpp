#include "RedDragon2.h"

RedDragon2* RedDragon2::create()
{
	RedDragon2* instance = new RedDragon2();

	instance->autorelease();

	return instance;
}

RedDragon2::RedDragon2() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

RedDragon2::~RedDragon2()
{
}
