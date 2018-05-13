#include "BatDemon.h"

BatDemon* BatDemon::create()
{
	BatDemon* instance = new BatDemon();

	instance->autorelease();

	return instance;
}

BatDemon::BatDemon() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_BatDemon_Animations,
	false,
	Size(726.0f, 1024.0f),
	0.23f,
	Vec2(-32.0f, -512.0f))
{
}

BatDemon::~BatDemon()
{
}
