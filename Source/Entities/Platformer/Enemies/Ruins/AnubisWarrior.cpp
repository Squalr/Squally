#include "AnubisWarrior.h"

const std::string AnubisWarrior::MapKeyEnemyAnubisWarrior = "anubis_warrior";

AnubisWarrior* AnubisWarrior::deserialize(ValueMap* initProperties)
{
	AnubisWarrior* instance = new AnubisWarrior(initProperties);

	instance->autorelease();

	return instance;
}

AnubisWarrior::AnubisWarrior(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Ruins_Enemies_AnubisWarrior_Animations,
	PlatformerCollisionType::Enemy,
	Size(256.0f, 292.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

AnubisWarrior::~AnubisWarrior()
{
}
