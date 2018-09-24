#include "RockGolem.h"

const std::string RockGolem::KeyEnemyRockGolem = "rock_golem";

RockGolem* RockGolem::deserialize(ValueMap* initProperties)
{
	RockGolem* instance = new RockGolem(initProperties);

	instance->autorelease();

	return instance;
}

RockGolem::RockGolem(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Caverns_Enemies_RockGolem_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(1108.0f, 1024.0f),
	0.4f,
	Vec2(0.0f, 0.0f))
{
}

RockGolem::~RockGolem()
{
}
