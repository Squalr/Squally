#include "TinyRockGolem.h"

TinyRockGolem* TinyRockGolem::create()
{
	TinyRockGolem* instance = new TinyRockGolem();

	instance->autorelease();

	return instance;
}

TinyRockGolem::TinyRockGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

TinyRockGolem::~TinyRockGolem()
{
}
