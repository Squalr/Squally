#include "YetiWarrior.h"

const std::string YetiWarrior::KeyEnemyYetiWarrior = "yeti_warrior";

YetiWarrior* YetiWarrior::deserialize(ValueMap* initProperties)
{
	YetiWarrior* instance = new YetiWarrior(initProperties);

	instance->autorelease();

	return instance;
}

YetiWarrior::YetiWarrior(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Snow_YetiWarrior_Animations,
	false,
	Size(380.0f, 572.0f),
	0.4f,
	Vec2(24.0f, -280.0f))
{
}

YetiWarrior::~YetiWarrior()
{
}
