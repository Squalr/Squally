#include "MantisDragon.h"

MantisDragon* MantisDragon::create()
{
	MantisDragon* instance = new MantisDragon();

	instance->autorelease();

	return instance;
}

MantisDragon::MantisDragon() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

MantisDragon::~MantisDragon()
{
}
