#include "ForestGolem.h"

ForestGolem* ForestGolem::create()
{
	ForestGolem* instance = new ForestGolem();

	instance->autorelease();

	return instance;
}

ForestGolem::ForestGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_ForestGolem_Animations,
	false)
{
}

ForestGolem::~ForestGolem()
{
}
