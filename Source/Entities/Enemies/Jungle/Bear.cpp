#include "Bear.h"

Bear* Bear::create()
{
	Bear* instance = new Bear();

	instance->autorelease();

	return instance;
}

Bear::Bear() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

Bear::~Bear()
{
}
