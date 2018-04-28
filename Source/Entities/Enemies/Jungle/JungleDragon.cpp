#include "JungleDragon.h"

JungleDragon* JungleDragon::create()
{
	JungleDragon* instance = new JungleDragon();

	instance->autorelease();

	return instance;
}

JungleDragon::JungleDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

JungleDragon::~JungleDragon()
{
}
