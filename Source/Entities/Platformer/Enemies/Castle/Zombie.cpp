#include "Zombie.h"

const std::string Zombie::KeyEnemyZombie = "zombie";

Zombie* Zombie::deserialize(ValueMap* initProperties)
{
	Zombie* instance = new Zombie(initProperties);

	instance->autorelease();

	return instance;
}

Zombie::Zombie(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Zombie_Animations,
	false,
	Size(114.0f, 208.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Zombie::~Zombie()
{
}
