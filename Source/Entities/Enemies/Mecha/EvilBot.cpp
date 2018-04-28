#include "EvilBot.h"

EvilBot* EvilBot::create()
{
	EvilBot* instance = new EvilBot();

	instance->autorelease();

	return instance;
}

EvilBot::EvilBot() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

EvilBot::~EvilBot()
{
}
