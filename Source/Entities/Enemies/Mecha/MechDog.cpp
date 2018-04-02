#include "MechDog.h"

MechDog* MechDog::create()
{
	MechDog* instance = new MechDog();

	instance->autorelease();

	return instance;
}

MechDog::MechDog() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

MechDog::~MechDog()
{
}
