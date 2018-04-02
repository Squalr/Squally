#include "RockGolem.h"

RockGolem* RockGolem::create()
{
	RockGolem* instance = new RockGolem();

	instance->autorelease();

	return instance;
}

RockGolem::RockGolem() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

RockGolem::~RockGolem()
{
}
