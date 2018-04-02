#include "RedDragon1.h"

RedDragon1* RedDragon1::create()
{
	RedDragon1* instance = new RedDragon1();

	instance->autorelease();

	return instance;
}

RedDragon1::RedDragon1() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

RedDragon1::~RedDragon1()
{
}
