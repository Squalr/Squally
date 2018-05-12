#include "Zombie.h"

Zombie* Zombie::create()
{
	Zombie* instance = new Zombie();

	instance->autorelease();

	return instance;
}

Zombie::Zombie() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_Zombie_Animations,
	false,
	Size(114.0f, 208.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Zombie::~Zombie()
{
}
