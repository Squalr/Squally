#include "Ghost.h"

const std::string Ghost::KeyEnemyGhost = "ghost";

Ghost* Ghost::deserialize(ValueMap* initProperties)
{
	Ghost* instance = new Ghost(initProperties);

	instance->autorelease();

	return instance;
}

Ghost::Ghost(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Ghost_Animations,
	false,
	Size(480.0f, 692.0f),
	0.3f,
	Vec2(-32.0f, -224.0f))
{
}

Ghost::~Ghost()
{
}
