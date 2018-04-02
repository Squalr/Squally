#include "PigGoblin.h"

PigGoblin* PigGoblin::create()
{
	PigGoblin* instance = new PigGoblin();

	instance->autorelease();

	return instance;
}

PigGoblin::PigGoblin() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

PigGoblin::~PigGoblin()
{
}
