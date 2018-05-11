#include "WaterElemental.h"

WaterElemental* WaterElemental::create()
{
	WaterElemental* instance = new WaterElemental();

	instance->autorelease();

	return instance;
}

WaterElemental::WaterElemental() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_WaterElemental_Animations,
	false)
{
}

WaterElemental::~WaterElemental()
{
}
