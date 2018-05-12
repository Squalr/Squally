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
	Size(980.0f, 1360.0f),
	0.17f,
	Vec2(0.0f, -680.0f))
{
}

TinyIceGolem::~TinyIceGolem()
{
}
