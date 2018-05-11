#include "Tigress.h"

Tigress* Tigress::create()
{
	Tigress* instance = new Tigress();

	instance->autorelease();

	return instance;
}

Tigress::Tigress() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_Tigress_Animations,
	false)
{
}

Tigress::~Tigress()
{
}
