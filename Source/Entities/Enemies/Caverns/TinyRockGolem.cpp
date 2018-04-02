#include "TinyRockGolem.h"

TinyRockGolem* TinyRockGolem::create()
{
	TinyRockGolem* instance = new TinyRockGolem();

	instance->autorelease();

	return instance;
}

TinyRockGolem::TinyRockGolem() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

TinyRockGolem::~TinyRockGolem()
{
}
