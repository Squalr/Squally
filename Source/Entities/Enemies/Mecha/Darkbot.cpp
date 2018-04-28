#include "DarkBot.h"

DarkBot* DarkBot::create()
{
	DarkBot* instance = new DarkBot();

	instance->autorelease();

	return instance;
}

DarkBot::DarkBot() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

DarkBot::~DarkBot()
{
}
