#include "EarthElemental.h"

const std::string EarthElemental::KeyEnemyEarthElemental = "earth_elemental";

EarthElemental* EarthElemental::create()
{
	EarthElemental* instance = new EarthElemental();

	instance->autorelease();

	return instance;
}

EarthElemental::EarthElemental() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_EarthElemental_Animations,
	false,
	Size(820.0f, 1480.0f),
	0.20f,
	Vec2(0.0f, -740.0f))
{
}

EarthElemental::~EarthElemental()
{
}
