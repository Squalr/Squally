#include "LavaGolem.h"

LavaGolem* LavaGolem::create()
{
	LavaGolem* instance = new LavaGolem();

	instance->autorelease();

	return instance;
}

LavaGolem::LavaGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

LavaGolem::~LavaGolem()
{
}
