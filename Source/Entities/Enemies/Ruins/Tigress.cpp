#include "Tigress.h"

Tigress* Tigress::create()
{
	Tigress* instance = new Tigress();

	instance->autorelease();

	return instance;
}

Tigress::Tigress() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_Tigress_Animations,
	false,
	Size(128.0f, 256.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Tigress::~Tigress()
{
}
