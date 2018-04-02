#include "Jack.h"

Jack* Jack::create()
{
	Jack* instance = new Jack();

	instance->autorelease();

	return instance;
}

Jack::Jack() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Jack::~Jack()
{
}
