#include "ForestGolem.h"

ForestGolem* ForestGolem::create()
{
	ForestGolem* instance = new ForestGolem();

	instance->autorelease();

	return instance;
}

ForestGolem::ForestGolem() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

ForestGolem::~ForestGolem()
{
}
