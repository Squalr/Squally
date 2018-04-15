#include "JungleDragon.h"

JungleDragon* JungleDragon::create()
{
	JungleDragon* instance = new JungleDragon();

	instance->autorelease();

	return instance;
}

JungleDragon::JungleDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

JungleDragon::~JungleDragon()
{
}
