#include "DarkBot.h"

DarkBot* DarkBot::create()
{
	DarkBot* instance = new DarkBot();

	instance->autorelease();

	return instance;
}

DarkBot::DarkBot() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

DarkBot::~DarkBot()
{
}
