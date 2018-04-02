#include "Penguin2.h"

Penguin2* Penguin2::create()
{
	Penguin2* instance = new Penguin2();

	instance->autorelease();

	return instance;
}

Penguin2::Penguin2() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Penguin2::~Penguin2()
{
}
