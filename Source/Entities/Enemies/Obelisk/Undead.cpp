#include "Undead.h"

Undead* Undead::create()
{
	Undead* instance = new Undead();

	instance->autorelease();

	return instance;
}

Undead::Undead() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Undead::~Undead()
{
}
