#include "Yeti2.h"

Yeti2* Yeti2::create()
{
	Yeti2* instance = new Yeti2();

	instance->autorelease();

	return instance;
}

Yeti2::Yeti2() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Yeti2::~Yeti2()
{
}
