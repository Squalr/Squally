#include "JungleDragon.h"

const std::string JungleDragon::KeyEnemyJungleDragon = "jungle_dragon";

JungleDragon* JungleDragon::deserialize(ValueMap* initProperties)
{
	JungleDragon* instance = new JungleDragon(initProperties);

	instance->autorelease();

	return instance;
}

JungleDragon::JungleDragon(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_JungleDragon_Animations,
	false,
	Size(640.0f, 356.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

JungleDragon::~JungleDragon()
{
}
