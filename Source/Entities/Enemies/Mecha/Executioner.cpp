#include "Executioner.h"

Executioner* Executioner::create()
{
	Executioner* instance = new Executioner();

	instance->autorelease();

	return instance;
}

Executioner::Executioner() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Executioner::~Executioner()
{
}
