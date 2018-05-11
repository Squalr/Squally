#include "TikiGolem.h"

TikiGolem* TikiGolem::create()
{
	TikiGolem* instance = new TikiGolem();

	instance->autorelease();

	return instance;
}

TikiGolem::TikiGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_TikiGolem_Animations,
	false)
{
}

TikiGolem::~TikiGolem()
{
}
