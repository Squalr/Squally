#include "VoidDemon.h"

VoidDemon* VoidDemon::create()
{
	VoidDemon* instance = new VoidDemon();

	instance->autorelease();

	return instance;
}

VoidDemon::VoidDemon() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_VoidDemon_Animations,
	false,
	Size(338.0f, 342.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

VoidDemon::~VoidDemon()
{
}
