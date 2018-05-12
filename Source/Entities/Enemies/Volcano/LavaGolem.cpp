#include "LavaGolem.h"

LavaGolem* LavaGolem::create()
{
	LavaGolem* instance = new LavaGolem();

	instance->autorelease();

	return instance;
}

LavaGolem::LavaGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_LavaGolem_Animations,
	false,
	Size(820.0f, 1480.0f),
	0.20f,
	Vec2(0.0f, -740.0f))
{
}

LavaGolem::~LavaGolem()
{
}
