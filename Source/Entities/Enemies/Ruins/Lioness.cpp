#include "Lioness.h"

Lioness* Lioness::create()
{
	Lioness* instance = new Lioness();

	instance->autorelease();

	return instance;
}

Lioness::Lioness() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Lioness::~Lioness()
{
}
