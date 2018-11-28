#include "MummyPriest.h"

const std::string MummyPriest::MapKeyEnemyMummyPriest = "mummy_priest";

MummyPriest* MummyPriest::deserialize(ValueMap* initProperties)
{
	MummyPriest* instance = new MummyPriest(initProperties);

	instance->autorelease();

	return instance;
}

MummyPriest::MummyPriest(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Ruins_Enemies_MummyPriest_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(128.0f, 256.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

MummyPriest::~MummyPriest()
{
}
