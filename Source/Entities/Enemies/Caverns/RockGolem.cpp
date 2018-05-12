#include "RockGolem.h"

RockGolem* RockGolem::create()
{
	RockGolem* instance = new RockGolem();

	instance->autorelease();

	return instance;
}

RockGolem::RockGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_RockGolem_Animations,
	false,
	Size(1108.0f, 1024.0f),
	0.4f,
	Vec2(0.0f, 0.0f))
{
}

RockGolem::~RockGolem()
{
}
