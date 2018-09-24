#include "DarkDragon.h"

const std::string DarkDragon::KeyEnemyDarkDragon = "dark_dragon";

DarkDragon* DarkDragon::deserialize(ValueMap* initProperties)
{
	DarkDragon* instance = new DarkDragon(initProperties);

	instance->autorelease();

	return instance;
}

DarkDragon::DarkDragon(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Obelisk_Enemies_DarkDragon_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(658.0f, 412.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

DarkDragon::~DarkDragon()
{
}
