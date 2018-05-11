#include "FireElemental.h"

FireElemental* FireElemental::create()
{
	FireElemental* instance = new FireElemental();

	instance->autorelease();

	return instance;
}

FireElemental::FireElemental() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_FireElemental_Animations,
	false)
{
}

FireElemental::~FireElemental()
{
}
