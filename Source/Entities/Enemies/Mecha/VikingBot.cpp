#include "VikingBot.h"

VikingBot* VikingBot::create()
{
	VikingBot* instance = new VikingBot();

	instance->autorelease();

	return instance;
}

VikingBot::VikingBot() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

VikingBot::~VikingBot()
{
}
