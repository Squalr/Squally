#include "DarkDragon.h"

DarkDragon* DarkDragon::create()
{
	DarkDragon* instance = new DarkDragon();

	instance->autorelease();

	return instance;
}

DarkDragon::DarkDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_DarkDragon_Animations,
	false,
	Size(658.0f, 412.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

DarkDragon::~DarkDragon()
{
}
