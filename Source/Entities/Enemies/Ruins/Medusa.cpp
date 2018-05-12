#include "Medusa.h"

Medusa* Medusa::create()
{
	Medusa* instance = new Medusa();

	instance->autorelease();

	return instance;
}

Medusa::Medusa() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_Medusa_Animations,
	false,
	Size(224.0f, 304.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Medusa::~Medusa()
{
}
