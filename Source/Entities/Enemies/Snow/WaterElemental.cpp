#include "WaterElemental.h"

WaterElemental* WaterElemental::create()
{
	WaterElemental* instance = new WaterElemental();

	instance->autorelease();

	return instance;
}

WaterElemental::WaterElemental() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_WaterElemental_Animations,
	false,
	Size(820.0f, 1480.0f),
	0.20f,
	Vec2(0.0f, -740.0f))
{
}

WaterElemental::~WaterElemental()
{
}
