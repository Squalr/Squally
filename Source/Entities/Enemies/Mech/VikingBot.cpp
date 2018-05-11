#include "VikingBot.h"

VikingBot* VikingBot::create()
{
	VikingBot* instance = new VikingBot();

	instance->autorelease();

	return instance;
}

VikingBot::VikingBot() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_VikingBot_Animations,
	false)
{
}

VikingBot::~VikingBot()
{
}
