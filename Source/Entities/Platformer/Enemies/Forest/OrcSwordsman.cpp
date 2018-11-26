#include "OrcSwordsman.h"

const std::string OrcSwordsman::MapKeyEnemyOrcSwordsman = "orc_swordsman";

OrcSwordsman* OrcSwordsman::deserialize(ValueMap* initProperties)
{
	OrcSwordsman* instance = new OrcSwordsman(initProperties);

	instance->autorelease();

	return instance;
}

OrcSwordsman::OrcSwordsman(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Forest_Enemies_OrcSwordsman_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(256.0f, 228.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

OrcSwordsman::~OrcSwordsman()
{
}
