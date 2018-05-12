#include "TinyIceGolem.h"

TinyIceGolem* TinyIceGolem::create()
{
	TinyIceGolem* instance = new TinyIceGolem();

	instance->autorelease();

	return instance;
}

TinyIceGolem::TinyIceGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_TinyIceGolem_Animations,
	false,
	Size(820.0f, 1480.0f),
	0.20f,
	Vec2(0.0f, -740.0f))
{
}

TinyIceGolem::~TinyIceGolem()
{
}
