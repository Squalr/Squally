#include "DarkDragon.h"

DarkDragon* DarkDragon::create()
{
	DarkDragon* instance = new DarkDragon();

	instance->autorelease();

	return instance;
}

DarkDragon::DarkDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

DarkDragon::~DarkDragon()
{
}
