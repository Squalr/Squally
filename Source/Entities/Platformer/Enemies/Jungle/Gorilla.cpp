#include "Gorilla.h"

const std::string Gorilla::MapKeyEnemyGorilla = "gorilla";

Gorilla* Gorilla::deserialize(ValueMap* initProperties)
{
	Gorilla* instance = new Gorilla(initProperties);

	instance->autorelease();

	return instance;
}

Gorilla::Gorilla(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_Enemies_Gorilla_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(278.0f, 288.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Gorilla::~Gorilla()
{
}
