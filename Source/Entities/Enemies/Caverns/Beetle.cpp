#include "Beetle.h"

Beetle* Beetle::create()
{
	Beetle* instance = new Beetle();

	instance->autorelease();

	return instance;
}

Beetle::Beetle() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Beetle::~Beetle()
{
}
