#include "BossKrampus.h"

BossKrampus* BossKrampus::create()
{
	BossKrampus* instance = new BossKrampus();

	instance->autorelease();

	return instance;
}

BossKrampus::BossKrampus() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

BossKrampus::~BossKrampus()
{
}
