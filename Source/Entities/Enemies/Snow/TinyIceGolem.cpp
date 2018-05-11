#include "TinyIceGolem.h"

TinyIceGolem* TinyIceGolem::create()
{
	TinyIceGolem* instance = new TinyIceGolem();

	instance->autorelease();

	return instance;
}

TinyIceGolem::TinyIceGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_TinyIceGolem_Animations,
	false)
{
}

TinyIceGolem::~TinyIceGolem()
{
}
