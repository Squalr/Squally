#include "YetiWarrior.h"

const std::string YetiWarrior::MapKeyEnemyYetiWarrior = "yeti_warrior";

YetiWarrior* YetiWarrior::deserialize(ValueMap* initProperties)
{
	YetiWarrior* instance = new YetiWarrior(initProperties);

	instance->autorelease();

	return instance;
}

YetiWarrior::YetiWarrior(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Snow_Enemies_YetiWarrior_Animations,
	PlatformerCollisionType::Enemy,
	Size(380.0f, 572.0f),
	0.4f,
	Vec2(24.0f, -280.0f))
{
}

YetiWarrior::~YetiWarrior()
{
}
