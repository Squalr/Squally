#include "DemonDragon.h"

const std::string DemonDragon::MapKeyEnemyDemonDragon = "demon_dragon";

DemonDragon* DemonDragon::deserialize(ValueMap* initProperties)
{
	DemonDragon* instance = new DemonDragon(initProperties);

	instance->autorelease();

	return instance;
}

DemonDragon::DemonDragon(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Volcano_Enemies_DemonDragon_Animations,
	PlatformerCollisionType::Enemy,
	Size(340.0f, 360.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
}

DemonDragon::~DemonDragon()
{
}
