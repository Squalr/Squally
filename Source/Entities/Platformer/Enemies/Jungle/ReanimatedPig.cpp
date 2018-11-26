#include "ReanimatedPig.h"

const std::string ReanimatedPig::MapKeyEnemyReanimatedPig = "reanimated_pig";

ReanimatedPig* ReanimatedPig::deserialize(ValueMap* initProperties)
{
	ReanimatedPig* instance = new ReanimatedPig(initProperties);

	instance->autorelease();

	return instance;
}

ReanimatedPig::ReanimatedPig(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Jungle_Enemies_ReanimatedPig_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(256.0f, 240.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

ReanimatedPig::~ReanimatedPig()
{
}
