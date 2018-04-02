#include "Abomination.h"

Abomination* Abomination::create()
{
	Abomination* instance = new Abomination();

	instance->autorelease();

	return instance;
}

Abomination::Abomination() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Abomination::~Abomination()
{
}
