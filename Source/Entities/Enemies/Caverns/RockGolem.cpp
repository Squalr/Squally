#include "RockGolem.h"

RockGolem* RockGolem::create()
{
	RockGolem* instance = new RockGolem();

	instance->autorelease();

	return instance;
}

RockGolem::RockGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_RockGolem_Animations,
	false)
{
}

RockGolem::~RockGolem()
{
}
