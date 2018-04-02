#include "PurpleDino.h"

PurpleDino* PurpleDino::create()
{
	PurpleDino* instance = new PurpleDino();

	instance->autorelease();

	return instance;
}

PurpleDino::PurpleDino() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

PurpleDino::~PurpleDino()
{
}
