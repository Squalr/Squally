#include "MechDestroyer.h"

MechDestroyer* MechDestroyer::create()
{
	MechDestroyer* instance = new MechDestroyer();

	instance->autorelease();

	return instance;
}

MechDestroyer::MechDestroyer() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

MechDestroyer::~MechDestroyer()
{
}
