#include "BossFrostGolem.h"

BossFrostGolem* BossFrostGolem::create()
{
	BossFrostGolem* instance = new BossFrostGolem();

	instance->autorelease();

	return instance;
}

BossFrostGolem::BossFrostGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

BossFrostGolem::~BossFrostGolem()
{
}
