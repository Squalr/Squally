#include "EarthElemental.h"

EarthElemental* EarthElemental::create()
{
	EarthElemental* instance = new EarthElemental();

	instance->autorelease();

	return instance;
}

EarthElemental::EarthElemental() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_EarthElemental_Animations,
	false,
	Size(1024.0f, 960.0f),
	0.20f,
	Vec2(0.0f, -480.0f))
{
}

EarthElemental::~EarthElemental()
{
}
