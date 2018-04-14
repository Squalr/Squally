#include "BossDemon.h"

BossDemon* BossDemon::create()
{
	BossDemon* instance = new BossDemon();

	instance->autorelease();

	return instance;
}

BossDemon::BossDemon() : Enemy::Enemy()
{
	this->initializeEnemy2(
		Resources::Entities_Environment_Lava_BossDemonKing_Animations,
		"Idle",
		"Walk",
		true
	);
}

BossDemon::~BossDemon()
{
}
