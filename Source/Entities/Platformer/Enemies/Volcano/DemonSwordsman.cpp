#include "DemonSwordsman.h"

const std::string DemonSwordsman::MapKeyEnemyDemonSwordsman = "demon_swordsman";

DemonSwordsman* DemonSwordsman::deserialize(ValueMap* initProperties)
{
	DemonSwordsman* instance = new DemonSwordsman(initProperties);

	instance->autorelease();

	return instance;
}

DemonSwordsman::DemonSwordsman(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Volcano_Enemies_DemonSwordsman_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(212.0f, 268.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
}

DemonSwordsman::~DemonSwordsman()
{
}
