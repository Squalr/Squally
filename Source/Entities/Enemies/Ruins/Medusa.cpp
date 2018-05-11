#include "Medusa.h"

Medusa* Medusa::create()
{
	Medusa* instance = new Medusa();

	instance->autorelease();

	return instance;
}

Medusa::Medusa() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_Medusa_Animations,
	false)
{
}

Medusa::~Medusa()
{
}
