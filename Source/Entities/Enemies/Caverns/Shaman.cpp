#include "Shaman.h"

Shaman* Shaman::create()
{
	Shaman* instance = new Shaman();

	instance->autorelease();

	return instance;
}

Shaman::Shaman() : Enemy::Enemy(
	Resources::Entities_Environment_Caverns_Shaman_Animations,
	false)
{
}

Shaman::~Shaman()
{
}
