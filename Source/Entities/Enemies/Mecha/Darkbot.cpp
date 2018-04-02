#include "DarkBot.h"

DarkBot* DarkBot::create()
{
	DarkBot* instance = new DarkBot();

	instance->autorelease();

	return instance;
}

DarkBot::DarkBot() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

DarkBot::~DarkBot()
{
}
