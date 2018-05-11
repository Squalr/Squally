#include "Zombie.h"

Zombie* Zombie::create()
{
	Zombie* instance = new Zombie();

	instance->autorelease();

	return instance;
}

Zombie::Zombie() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_Zombie_Animations,
	false)
{
}

Zombie::~Zombie()
{
}
