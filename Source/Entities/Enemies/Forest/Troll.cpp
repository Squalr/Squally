#include "Troll.h"

Troll* Troll::create()
{
	Troll* instance = new Troll();

	instance->autorelease();

	return instance;
}

Troll::Troll() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Troll::~Troll()
{
}
