#include "ForestGolem.h"

const std::string ForestGolem::MapKeyEnemyForestGolem = "forest_golem";

ForestGolem* ForestGolem::deserialize(ValueMap* initProperties)
{
	ForestGolem* instance = new ForestGolem(initProperties);

	instance->autorelease();

	return instance;
}

ForestGolem::ForestGolem(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Caverns_Enemies_ForestGolem_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(768.0f, 840.0f),
	0.30f,
	Vec2(0.0f, -420.0f))
{
}

ForestGolem::~ForestGolem()
{
}
