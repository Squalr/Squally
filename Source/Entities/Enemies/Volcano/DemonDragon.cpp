#include "DemonDragon.h"

DemonDragon* DemonDragon::create()
{
	DemonDragon* instance = new DemonDragon();

	instance->autorelease();

	return instance;
}

DemonDragon::DemonDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_DemonDragon_Animations,
	false,
	Size(340.0f, 360.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

DemonDragon::~DemonDragon()
{
}
