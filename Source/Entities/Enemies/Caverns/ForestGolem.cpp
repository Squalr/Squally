#include "ForestGolem.h"

ForestGolem* ForestGolem::create()
{
	ForestGolem* instance = new ForestGolem();

	instance->autorelease();

	return instance;
}

ForestGolem::ForestGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

ForestGolem::~ForestGolem()
{
}
