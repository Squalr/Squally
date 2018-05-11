#include "EarthGolem.h"

EarthGolem* EarthGolem::create()
{
	EarthGolem* instance = new EarthGolem();

	instance->autorelease();

	return instance;
}

EarthGolem::EarthGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_EarthGolem_Animations,
	false)
{
}

EarthGolem::~EarthGolem()
{
}
