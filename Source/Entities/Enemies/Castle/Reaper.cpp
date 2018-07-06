#include "Reaper.h"

const std::string Reaper::KeyEnemyReaper = "reaper";

Reaper* Reaper::deserialize(ValueMap* initProperties)
{
	Reaper* instance = new Reaper(initProperties);

	instance->autorelease();

	return instance;
}

Reaper::Reaper(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Reaper_Animations,
	false,
	Size(196.0f, 512.0f),
	0.8f,
	Vec2(0.0f, -128.0f))
{
}

Reaper::~Reaper()
{
}
