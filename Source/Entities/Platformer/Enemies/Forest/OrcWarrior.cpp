#include "OrcWarrior.h"

const std::string OrcWarrior::MapKeyEnemyOrcWarrior = "orc_warrior";

OrcWarrior* OrcWarrior::deserialize(ValueMap* initProperties)
{
	OrcWarrior* instance = new OrcWarrior(initProperties);

	instance->autorelease();

	return instance;
}

OrcWarrior::OrcWarrior(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Forest_Enemies_OrcWarrior_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(256.0f, 228.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

OrcWarrior::~OrcWarrior()
{
}
