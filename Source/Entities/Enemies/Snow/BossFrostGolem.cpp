#include "BossFrostGolem.h"

BossFrostGolem* BossFrostGolem::create()
{
	BossFrostGolem* instance = new BossFrostGolem();

	instance->autorelease();

	return instance;
}

BossFrostGolem::BossFrostGolem() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

BossFrostGolem::~BossFrostGolem()
{
}
