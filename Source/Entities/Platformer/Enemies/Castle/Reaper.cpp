#include "Reaper.h"

const std::string Reaper::KeyEnemyReaper = "reaper";

Reaper* Reaper::deserialize(ValueMap* initProperties)
{
	Reaper* instance = new Reaper(initProperties);

	instance->autorelease();

	return instance;
}

Reaper::Reaper(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Enemies_Reaper_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(196.0f, 512.0f),
	0.8f,
	Vec2(0.0f, -128.0f))
{
}

Reaper::~Reaper()
{
}
