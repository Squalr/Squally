#include "ForestGolem.h"

ForestGolem* ForestGolem::create()
{
	ForestGolem* instance = new ForestGolem();

	instance->autorelease();

	return instance;
}

ForestGolem::ForestGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_ForestGolem_Animations,
	false,
	Size(768.0f, 840.0f),
	0.30f,
	Vec2(0.0f, -420.0f))
{
}

ForestGolem::~ForestGolem()
{
}
