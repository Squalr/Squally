#include "EvilBot.h"

EvilBot* EvilBot::create()
{
	EvilBot* instance = new EvilBot();

	instance->autorelease();

	return instance;
}

EvilBot::EvilBot() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

EvilBot::~EvilBot()
{
}
