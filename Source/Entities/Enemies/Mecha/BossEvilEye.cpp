#include "BossEvilEye.h"

BossEvilEye* BossEvilEye::create()
{
	BossEvilEye* instance = new BossEvilEye();

	instance->autorelease();

	return instance;
}

BossEvilEye::BossEvilEye() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

BossEvilEye::~BossEvilEye()
{
}
