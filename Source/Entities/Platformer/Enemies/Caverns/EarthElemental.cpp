#include "EarthElemental.h"

const std::string EarthElemental::MapKeyEnemyEarthElemental = "earth_elemental";

EarthElemental* EarthElemental::deserialize(ValueMap* initProperties)
{
	EarthElemental* instance = new EarthElemental(initProperties);

	instance->autorelease();

	return instance;
}

EarthElemental::EarthElemental(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Caverns_Enemies_EarthElemental_Animations,
	PlatformerCollisionType::Enemy,
	Size(820.0f, 1480.0f),
	0.20f,
	Vec2(0.0f, -740.0f))
{
}

EarthElemental::~EarthElemental()
{
}
