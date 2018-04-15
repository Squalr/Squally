#include "BossWitch.h"

BossWitch* BossWitch::create()
{
	BossWitch* instance = new BossWitch();

	instance->autorelease();

	return instance;
}

BossWitch::BossWitch() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing", 
	false)
{
}

BossWitch::~BossWitch()
{
}
