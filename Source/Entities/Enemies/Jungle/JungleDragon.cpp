#include "JungleDragon.h"

JungleDragon* JungleDragon::create()
{
	JungleDragon* instance = new JungleDragon();

	instance->autorelease();

	return instance;
}

JungleDragon::JungleDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_JungleDragon_Animations,
	false,
	Size(640.0f, 356.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

JungleDragon::~JungleDragon()
{
}
