#include "BossKrampus.h"

BossKrampus* BossKrampus::create()
{
	BossKrampus* instance = new BossKrampus();

	instance->autorelease();

	return instance;
}

BossKrampus::BossKrampus() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_BossKrampus_Animations,
	false,
	Size(396.0f, 412.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

BossKrampus::~BossKrampus()
{
}
