#include "GreenDragon.h"

GreenDragon* GreenDragon::create()
{
	GreenDragon* instance = new GreenDragon();

	instance->autorelease();

	return instance;
}

GreenDragon::GreenDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

GreenDragon::~GreenDragon()
{
}
