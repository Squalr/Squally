#include "ZombieErlic.h"

const std::string ZombieErlic::MapKeyEnemyZombieErlic = "zombie_erlic";

ZombieErlic* ZombieErlic::deserialize(ValueMap* initProperties)
{
	ZombieErlic* instance = new ZombieErlic(initProperties);

	instance->autorelease();

	return instance;
}

ZombieErlic::ZombieErlic(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Castle_Enemies_ZombieErlic_Animations,
	PlatformerCollisionType::Enemy,
	Size(114.0f, 208.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

ZombieErlic::~ZombieErlic()
{
}
