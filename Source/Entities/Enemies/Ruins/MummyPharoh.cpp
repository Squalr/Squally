#include "MummyPharoh.h"

MummyPharoh* MummyPharoh::create()
{
	MummyPharoh* instance = new MummyPharoh();

	instance->autorelease();

	return instance;
}

MummyPharoh::MummyPharoh() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

MummyPharoh::~MummyPharoh()
{
}
