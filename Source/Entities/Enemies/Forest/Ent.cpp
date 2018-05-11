#include "Ent.h"

Ent* Ent::create()
{
	Ent* instance = new Ent();

	instance->autorelease();

	return instance;
}

Ent::Ent() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_Ent_Animations,
	false)
{
}

Ent::~Ent()
{
}
