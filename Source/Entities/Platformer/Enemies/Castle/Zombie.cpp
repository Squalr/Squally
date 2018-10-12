#include "Zombie.h"

const std::string Zombie::MapKeyEnemyZombie = "zombie";

Zombie* Zombie::deserialize(ValueMap* initProperties)
{
	Zombie* instance = new Zombie(initProperties);

	instance->autorelease();

	return instance;
}

Zombie::Zombie(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Enemies_Zombie_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(114.0f, 208.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Zombie::~Zombie()
{
}
