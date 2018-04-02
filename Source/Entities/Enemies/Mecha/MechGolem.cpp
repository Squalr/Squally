#include "MechGolem.h"

MechGolem* MechGolem::create()
{
	MechGolem* instance = new MechGolem();

	instance->autorelease();

	return instance;
}

MechGolem::MechGolem() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

MechGolem::~MechGolem()
{
}
