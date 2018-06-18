#include "VikingBot.h"

const std::string VikingBot::KeyEnemyVikingBot = "viking_bot";

VikingBot* VikingBot::create()
{
	VikingBot* instance = new VikingBot();

	instance->autorelease();

	return instance;
}

VikingBot::VikingBot() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_VikingBot_Animations,
	false,
	Size(768.0f, 960.0f),
	0.5f,
	Vec2(-332.0f, 0.0f))
{
}

VikingBot::~VikingBot()
{
}
