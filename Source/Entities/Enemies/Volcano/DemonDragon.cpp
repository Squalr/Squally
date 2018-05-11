#include "DemonDragon.h"

DemonDragon* DemonDragon::create()
{
	DemonDragon* instance = new DemonDragon();

	instance->autorelease();

	return instance;
}

DemonDragon::DemonDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_DemonDragon_Animations,
	false)
{
}

DemonDragon::~DemonDragon()
{
}
