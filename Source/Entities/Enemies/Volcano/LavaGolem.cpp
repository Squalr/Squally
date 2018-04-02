#include "LavaGolem.h"

LavaGolem* LavaGolem::create()
{
	LavaGolem* instance = new LavaGolem();

	instance->autorelease();

	return instance;
}

LavaGolem::LavaGolem() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

LavaGolem::~LavaGolem()
{
}
