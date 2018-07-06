#include "Troll.h"

const std::string Troll::KeyEnemyTroll = "troll";

Troll* Troll::deserialize(ValueMap* initProperties)
{
	Troll* instance = new Troll(initProperties);

	instance->autorelease();

	return instance;
}

Troll::Troll(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Forest_Troll_Animations,
	false,
	Size(256.0f, 248.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Troll::~Troll()
{
}
