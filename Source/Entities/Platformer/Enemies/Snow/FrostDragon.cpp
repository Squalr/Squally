#include "FrostDragon.h"

const std::string FrostDragon::KeyEnemyFrostDragon = "frost_dragon";

FrostDragon* FrostDragon::deserialize(ValueMap* initProperties)
{
	FrostDragon* instance = new FrostDragon(initProperties);

	instance->autorelease();

	return instance;
}

FrostDragon::FrostDragon(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Snow_FrostDragon_Animations,
	false,
	Size(720.0f, 356.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

FrostDragon::~FrostDragon()
{
}
