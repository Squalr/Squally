#include "MiteBot.h"

MiteBot* MiteBot::create()
{
	MiteBot* instance = new MiteBot();

	instance->autorelease();

	return instance;
}

MiteBot::MiteBot() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_MiteBot_Animations,
	false,
	Size(420.0f, 296.0f),
	0.4f,
	Vec2(0.0f, 24.0f))
{
}

MiteBot::~MiteBot()
{
}
