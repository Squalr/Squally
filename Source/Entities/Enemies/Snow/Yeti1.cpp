#include "Yeti1.h"

Yeti1* Yeti1::create()
{
	Yeti1* instance = new Yeti1();

	instance->autorelease();

	return instance;
}

Yeti1::Yeti1() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Yeti1::~Yeti1()
{
}
