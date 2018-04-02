#include "DarkDragon.h"

DarkDragon* DarkDragon::create()
{
	DarkDragon* instance = new DarkDragon();

	instance->autorelease();

	return instance;
}

DarkDragon::DarkDragon() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

DarkDragon::~DarkDragon()
{
}
