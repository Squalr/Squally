#include "Yeti3.h"

Yeti3* Yeti3::create()
{
	Yeti3* instance = new Yeti3();

	instance->autorelease();

	return instance;
}

Yeti3::Yeti3() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Yeti3::~Yeti3()
{
}
