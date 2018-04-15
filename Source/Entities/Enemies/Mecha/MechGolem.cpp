#include "MechGolem.h"

MechGolem* MechGolem::create()
{
	MechGolem* instance = new MechGolem();

	instance->autorelease();

	return instance;
}

MechGolem::MechGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

MechGolem::~MechGolem()
{
}
