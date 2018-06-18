#include "LavaGolem.h"

const std::string LavaGolem::KeyEnemyLavaGolem = "lava_golem";

LavaGolem* LavaGolem::create()
{
	LavaGolem* instance = new LavaGolem();

	instance->autorelease();

	return instance;
}

LavaGolem::LavaGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_LavaGolem_Animations,
	false,
	Size(980.0f, 1200.0f),
	0.17f,
	Vec2(0.0f, -600.0f))
{
}

LavaGolem::~LavaGolem()
{
}
