#include "IceGolem.h"

IceGolem* IceGolem::create()
{
	IceGolem* instance = new IceGolem();

	instance->autorelease();

	return instance;
}

IceGolem::IceGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

IceGolem::~IceGolem()
{
}
