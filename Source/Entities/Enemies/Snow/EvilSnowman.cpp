#include "EvilSnowman.h"

const std::string EvilSnowman::KeyEnemyEvilSnowman = "evil_snowman";

EvilSnowman* EvilSnowman::deserialize(ValueMap* initProperties)
{
	EvilSnowman* instance = new EvilSnowman(initProperties);

	instance->autorelease();

	return instance;
}

EvilSnowman::EvilSnowman(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Snow_EvilSnowman_Animations,
	false,
	Size(420.0f, 420.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

EvilSnowman::~EvilSnowman()
{
}
