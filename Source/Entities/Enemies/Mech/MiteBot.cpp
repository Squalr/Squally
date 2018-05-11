#include "MiteBot.h"

MiteBot* MiteBot::create()
{
	MiteBot* instance = new MiteBot();

	instance->autorelease();

	return instance;
}

MiteBot::MiteBot() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_MiteBot_Animations,
	false)
{
}

MiteBot::~MiteBot()
{
}
