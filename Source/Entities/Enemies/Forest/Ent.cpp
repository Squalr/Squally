#include "Ent.h"

Ent* Ent::create()
{
	Ent* instance = new Ent();

	instance->autorelease();

	return instance;
}

Ent::Ent() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_Ent_Animations,
	false,
	Size(512.0f, 960.0f),
	0.3f,
	Vec2(24.0f, -452.0f))
{
}

Ent::~Ent()
{
}
