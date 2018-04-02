#include "DemonWarrior1.h"

DemonWarrior1* DemonWarrior1::create()
{
	DemonWarrior1* instance = new DemonWarrior1();

	instance->autorelease();

	return instance;
}

DemonWarrior1::DemonWarrior1() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

DemonWarrior1::~DemonWarrior1()
{
}
