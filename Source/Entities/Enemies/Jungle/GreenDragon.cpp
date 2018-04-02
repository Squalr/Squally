#include "GreenDragon.h"

GreenDragon* GreenDragon::create()
{
	GreenDragon* instance = new GreenDragon();

	instance->autorelease();

	return instance;
}

GreenDragon::GreenDragon() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

GreenDragon::~GreenDragon()
{
}
