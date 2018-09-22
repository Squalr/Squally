#include "EarthElemental.h"

const std::string EarthElemental::KeyEnemyEarthElemental = "earth_elemental";

EarthElemental* EarthElemental::deserialize(ValueMap* initProperties)
{
	EarthElemental* instance = new EarthElemental(initProperties);

	instance->autorelease();

	return instance;
}

EarthElemental::EarthElemental(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Caverns_Enemies_EarthElemental_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(820.0f, 1480.0f),
	0.20f,
	Vec2(0.0f, -740.0f))
{
}

EarthElemental::~EarthElemental()
{
}
