#include "WaterElemental.h"

const std::string WaterElemental::KeyEnemyWaterElemental = "water_elemental";

WaterElemental* WaterElemental::deserialize(ValueMap* initProperties)
{
	WaterElemental* instance = new WaterElemental(initProperties);

	instance->autorelease();

	return instance;
}

WaterElemental::WaterElemental(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Snow_Enemies_WaterElemental_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(820.0f, 1480.0f),
	0.20f,
	Vec2(0.0f, -740.0f))
{
}

WaterElemental::~WaterElemental()
{
}
