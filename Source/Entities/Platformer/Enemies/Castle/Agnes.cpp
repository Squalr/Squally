#include "Agnes.h"

const std::string Agnes::MapKeyEnemyAgnes = "agnes";

Agnes* Agnes::deserialize(ValueMap* initProperties)
{
	Agnes* instance = new Agnes(initProperties);

	instance->autorelease();

	return instance;
}

Agnes::Agnes(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Castle_Enemies_Agnes_Animations,
	PlatformerCollisionType::Enemy,
	Size(360.0f, 420.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Agnes::~Agnes()
{
}
