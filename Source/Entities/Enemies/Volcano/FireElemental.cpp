#include "FireElemental.h"

FireElemental* FireElemental::create()
{
	FireElemental* instance = new FireElemental();

	instance->autorelease();

	return instance;
}

FireElemental::FireElemental() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_FireElemental_Animations,
	false,
	Size(820.0f, 1480.0f),
	0.20f,
	Vec2(0.0f, -740.0f))
{
}

FireElemental::~FireElemental()
{
}
