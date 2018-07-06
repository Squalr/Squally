#include "Guard.h"

const std::string Guard::KeyEnemyGuard = "guard";

Guard* Guard::deserialize(ValueMap* initProperties)
{
	Guard* instance = new Guard(initProperties);

	instance->autorelease();

	return instance;
}

Guard::Guard(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Guard_Animations,
	false,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Guard::~Guard()
{
}
