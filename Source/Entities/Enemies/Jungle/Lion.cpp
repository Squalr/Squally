#include "Lion.h"

Lion* Lion::create()
{
	Lion* instance = new Lion();

	instance->autorelease();

	return instance;
}

Lion::Lion() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Lion::~Lion()
{
}
