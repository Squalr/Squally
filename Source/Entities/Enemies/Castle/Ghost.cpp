#include "Ghost.h"

Ghost* Ghost::create()
{
	Ghost* instance = new Ghost();

	instance->autorelease();

	return instance;
}

Ghost::Ghost() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Ghost::~Ghost()
{
}
