#include "Harpy.h"

Harpy* Harpy::create()
{
	Harpy* instance = new Harpy();

	instance->autorelease();

	return instance;
}

Harpy::Harpy() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Idle_0001, 
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Harpy::~Harpy()
{
}
