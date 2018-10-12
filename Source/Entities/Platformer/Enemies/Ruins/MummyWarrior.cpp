#include "MummyWarrior.h"

const std::string MummyWarrior::MapKeyEnemyMummyWarrior = "mummy_warrior";

MummyWarrior* MummyWarrior::deserialize(ValueMap* initProperties)
{
	MummyWarrior* instance = new MummyWarrior(initProperties);

	instance->autorelease();

	return instance;
}

MummyWarrior::MummyWarrior(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Ruins_Enemies_MummyWarrior_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(128.0f, 256.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

MummyWarrior::~MummyWarrior()
{
}
