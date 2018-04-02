#include "Snowman.h"

Snowman* Snowman::create()
{
	Snowman* instance = new Snowman();

	instance->autorelease();

	return instance;
}

Snowman::Snowman() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Snowman::~Snowman()
{
}
