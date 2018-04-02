#include "Reindeer.h"

Reindeer* Reindeer::create()
{
	Reindeer* instance = new Reindeer();

	instance->autorelease();

	return instance;
}

Reindeer::Reindeer() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Reindeer::~Reindeer()
{
}
