#include "TikiGolem.h"

TikiGolem* TikiGolem::create()
{
	TikiGolem* instance = new TikiGolem();

	instance->autorelease();

	return instance;
}

TikiGolem::TikiGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_TikiGolem_Animations,
	false,
	Size(284.0f, 256.0f),
	1.0f,
	Vec2(0.0f, -112.0f))
{
}

TikiGolem::~TikiGolem()
{
}
