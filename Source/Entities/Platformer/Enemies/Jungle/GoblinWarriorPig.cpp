#include "GoblinWarriorPig.h"

const std::string GoblinWarriorPig::MapKeyEnemyGoblinWarriorPig = "goblin_warrior_pig";

GoblinWarriorPig* GoblinWarriorPig::deserialize(ValueMap* initProperties)
{
	GoblinWarriorPig* instance = new GoblinWarriorPig(initProperties);

	instance->autorelease();

	return instance;
}

GoblinWarriorPig::GoblinWarriorPig(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Jungle_Enemies_GoblinWarriorPig_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(128.0f, 296.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

GoblinWarriorPig::~GoblinWarriorPig()
{
}
