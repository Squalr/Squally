#include "TinyIceGolem.h"

TinyIceGolem* TinyIceGolem::create()
{
	TinyIceGolem* instance = new TinyIceGolem();

	instance->autorelease();

	return instance;
}

TinyIceGolem::TinyIceGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

TinyIceGolem::~TinyIceGolem()
{
}
