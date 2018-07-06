#include "PigDemon.h"

const std::string PigDemon::KeyEnemyPigDemon = "pig_demon";

PigDemon* PigDemon::deserialize(ValueMap* initProperties)
{
	PigDemon* instance = new PigDemon(initProperties);

	instance->autorelease();

	return instance;
}

PigDemon::PigDemon(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_PigDemon_Animations,
	false,
	Size(256.0f, 240.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

PigDemon::~PigDemon()
{
}
