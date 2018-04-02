#include "Penguin1.h"

Penguin1* Penguin1::create()
{
	Penguin1* instance = new Penguin1();

	instance->autorelease();

	return instance;
}

Penguin1::Penguin1() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Penguin1::~Penguin1()
{
}
