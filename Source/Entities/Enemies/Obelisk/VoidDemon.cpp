#include "VoidDemon.h"

VoidDemon* VoidDemon::create()
{
	VoidDemon* instance = new VoidDemon();

	instance->autorelease();

	return instance;
}

VoidDemon::VoidDemon() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

VoidDemon::~VoidDemon()
{
}
