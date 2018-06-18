#include "VikingBotSmall.h"

const std::string VikingBotSmall::KeyEnemyVikingBotSmall = "viking_bot_small";

VikingBotSmall* VikingBotSmall::create()
{
	VikingBotSmall* instance = new VikingBotSmall();

	instance->autorelease();

	return instance;
}

VikingBotSmall::VikingBotSmall() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_VikingBotSmall_Animations,
	false,
	Size(768.0f, 768.0f),
	0.25f,
	Vec2(0.0f, 160.0f))
{
}

VikingBotSmall::~VikingBotSmall()
{
}
