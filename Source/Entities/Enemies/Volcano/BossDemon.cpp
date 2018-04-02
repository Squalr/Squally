#include "BossDemon.h"

BossDemon* BossDemon::create()
{
	BossDemon* instance = new BossDemon();

	instance->autorelease();

	return instance;
}

BossDemon::BossDemon() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

BossDemon::~BossDemon()
{
}
