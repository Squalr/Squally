#include "BigHandsBot.h"

BigHandsBot* BigHandsBot::create()
{
	BigHandsBot* instance = new BigHandsBot();

	instance->autorelease();

	return instance;
}

BigHandsBot::BigHandsBot() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

BigHandsBot::~BigHandsBot()
{
}
