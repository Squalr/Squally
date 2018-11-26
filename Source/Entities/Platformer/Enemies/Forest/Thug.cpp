#include "Thug.h"

const std::string Thug::MapKeyEnemyThug = "thug";

Thug* Thug::deserialize(ValueMap* initProperties)
{
	Thug* instance = new Thug(initProperties);

	instance->autorelease();

	return instance;
}

Thug::Thug(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Forest_Enemies_Thug_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(256.0f, 248.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Thug::~Thug()
{
}
