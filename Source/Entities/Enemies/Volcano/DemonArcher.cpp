#include "DemonArcher.h"

DemonArcher* DemonArcher::create()
{
	DemonArcher* instance = new DemonArcher();

	instance->autorelease();

	return instance;
}

DemonArcher::DemonArcher() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

DemonArcher::~DemonArcher()
{
}
