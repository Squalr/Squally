#include "IceGolem.h"

IceGolem* IceGolem::create()
{
	IceGolem* instance = new IceGolem();

	instance->autorelease();

	return instance;
}

IceGolem::IceGolem() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

IceGolem::~IceGolem()
{
}
