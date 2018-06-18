#include "EarthElemental.h"

const std::string EarthElemental::KeyEnemyEarthElemental = "earth_elemental";

EarthElemental* EarthElemental::deserialize(ValueMap* initProperties)
{
	EarthElemental* instance = new EarthElemental(initProperties);

	instance->autorelease();

	return instance;
}

EarthElemental::EarthElemental(ValueMap* initProperties) : Enemy(initProperties,
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
