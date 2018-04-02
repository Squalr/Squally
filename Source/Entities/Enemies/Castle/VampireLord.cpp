#include "VampireLord.h"

VampireLord* VampireLord::create()
{
	VampireLord* instance = new VampireLord();

	instance->autorelease();

	return instance;
}

VampireLord::VampireLord() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

VampireLord::~VampireLord()
{
}
