#include "BigHandsBot.h"

BigHandsBot* BigHandsBot::create()
{
	BigHandsBot* instance = new BigHandsBot();

	instance->autorelease();

	return instance;
}

BigHandsBot::BigHandsBot() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

BigHandsBot::~BigHandsBot()
{
}
