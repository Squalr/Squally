#include "Cyclops.h"

Cyclops* Cyclops::create()
{
	Cyclops* instance = new Cyclops();

	instance->autorelease();

	return instance;
}

Cyclops::Cyclops() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Cyclops::~Cyclops()
{
}
