#include "Rhinoman.h"

const std::string Rhinoman::MapKeyEnemyRhinoman = "rhinoman";

Rhinoman* Rhinoman::deserialize(ValueMap* initProperties)
{
	Rhinoman* instance = new Rhinoman(initProperties);

	instance->autorelease();

	return instance;
}

Rhinoman::Rhinoman(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Jungle_Enemies_Rhinoman_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(592.0f, 592.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Rhinoman::~Rhinoman()
{
}
