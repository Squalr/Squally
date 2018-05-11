#include "IceGolem.h"

IceGolem* IceGolem::create()
{
	IceGolem* instance = new IceGolem();

	instance->autorelease();

	return instance;
}

IceGolem::IceGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_BossIceGolem_Animations,
	false)
{
}

IceGolem::~IceGolem()
{
}
