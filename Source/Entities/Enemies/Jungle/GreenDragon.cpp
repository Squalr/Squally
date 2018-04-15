#include "GreenDragon.h"

GreenDragon* GreenDragon::create()
{
	GreenDragon* instance = new GreenDragon();

	instance->autorelease();

	return instance;
}

GreenDragon::GreenDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

GreenDragon::~GreenDragon()
{
}
