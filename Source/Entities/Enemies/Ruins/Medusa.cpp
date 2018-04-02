#include "Medusa.h"

Medusa* Medusa::create()
{
	Medusa* instance = new Medusa();

	instance->autorelease();

	return instance;
}

Medusa::Medusa() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Medusa::~Medusa()
{
}
