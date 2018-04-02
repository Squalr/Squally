#include "FrostDragon.h"

FrostDragon* FrostDragon::create()
{
	FrostDragon* instance = new FrostDragon();

	instance->autorelease();

	return instance;
}

FrostDragon::FrostDragon() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

FrostDragon::~FrostDragon()
{
}
