#include "GoblinElf.h"

const std::string GoblinElf::MapKeyEnemyGoblinElf = "goblin_elf";

GoblinElf* GoblinElf::deserialize(ValueMap* initProperties)
{
	GoblinElf* instance = new GoblinElf(initProperties);

	instance->autorelease();

	return instance;
}

GoblinElf::GoblinElf(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Snow_Enemies_GoblinElf_Animations,
	PlatformerCollisionType::Enemy,
	Size(140.0f, 296.0f),
	0.6f,
	Vec2(0.0f, 0.0f))
{
}

GoblinElf::~GoblinElf()
{
}
