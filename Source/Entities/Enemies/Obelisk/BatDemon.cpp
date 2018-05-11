#include "BatDemon.h"

BatDemon* BatDemon::create()
{
	BatDemon* instance = new BatDemon();

	instance->autorelease();

	return instance;
}

BatDemon::BatDemon() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_BatDemon_Animations,
	false)
{
}

BatDemon::~BatDemon()
{
}
