#include "EvilBot.h"

EvilBot* EvilBot::create()
{
	EvilBot* instance = new EvilBot();

	instance->autorelease();

	return instance;
}

EvilBot::EvilBot() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

EvilBot::~EvilBot()
{
}
