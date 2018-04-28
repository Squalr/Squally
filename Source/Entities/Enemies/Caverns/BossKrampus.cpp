#include "BossKrampus.h"

BossKrampus* BossKrampus::create()
{
	BossKrampus* instance = new BossKrampus();

	instance->autorelease();

	return instance;
}

BossKrampus::BossKrampus() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

BossKrampus::~BossKrampus()
{
}
