#include "IceGolem.h"

IceGolem* IceGolem::create()
{
	IceGolem* instance = new IceGolem();

	instance->autorelease();

	return instance;
}

IceGolem::IceGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_IceGolem_Animations,
	false,
	Size(1400.0f, 1120.0f),
	0.35f,
	Vec2(0.0f, 0.0f))
{
}

IceGolem::~IceGolem()
{
}
