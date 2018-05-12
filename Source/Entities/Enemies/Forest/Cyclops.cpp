#include "Cyclops.h"

Cyclops* Cyclops::create()
{
	Cyclops* instance = new Cyclops();

	instance->autorelease();

	return instance;
}

Cyclops::Cyclops() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_Cyclops_Animations,
	false,
	Size(296.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Cyclops::~Cyclops()
{
}
