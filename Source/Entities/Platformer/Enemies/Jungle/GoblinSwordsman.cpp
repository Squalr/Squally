#include "GoblinSwordsman.h"

const std::string GoblinSwordsman::KeyEnemyGoblinSwordsman = "goblin_swordsman";

GoblinSwordsman* GoblinSwordsman::deserialize(ValueMap* initProperties)
{
	GoblinSwordsman* instance = new GoblinSwordsman(initProperties);

	instance->autorelease();

	return instance;
}

GoblinSwordsman::GoblinSwordsman(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_GoblinSwordsman_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(312.0f, 512.0f),
	0.35f,
	Vec2(0.0f, -224.0f))
{
}

GoblinSwordsman::~GoblinSwordsman()
{
}
