#include "PigDemon.h"

PigDemon* PigDemon::create()
{
	PigDemon* instance = new PigDemon();

	instance->autorelease();

	return instance;
}

PigDemon::PigDemon() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

PigDemon::~PigDemon()
{
}
