#include "LavaGolem.h"

LavaGolem* LavaGolem::create()
{
	LavaGolem* instance = new LavaGolem();

	instance->autorelease();

	return instance;
}

LavaGolem::LavaGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_LavaGolem_Animations,
	false)
{
}

LavaGolem::~LavaGolem()
{
}
