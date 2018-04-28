#include "ForestGolem.h"

ForestGolem* ForestGolem::create()
{
	ForestGolem* instance = new ForestGolem();

	instance->autorelease();

	return instance;
}

ForestGolem::ForestGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

ForestGolem::~ForestGolem()
{
}
