#include "EarthGolem.h"

EarthGolem* EarthGolem::create()
{
	EarthGolem* instance = new EarthGolem();

	instance->autorelease();

	return instance;
}

EarthGolem::EarthGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_EarthGolem_Animations,
	false,
	Size(256.0f, 224.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

EarthGolem::~EarthGolem()
{
}
