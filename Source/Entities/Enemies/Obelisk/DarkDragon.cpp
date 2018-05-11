#include "DarkDragon.h"

DarkDragon* DarkDragon::create()
{
	DarkDragon* instance = new DarkDragon();

	instance->autorelease();

	return instance;
}

DarkDragon::DarkDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_DarkDragon_Animations,
	false)
{
}

DarkDragon::~DarkDragon()
{
}
