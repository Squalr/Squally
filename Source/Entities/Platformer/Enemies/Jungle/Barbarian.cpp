#include "Barbarian.h"

const std::string Barbarian::MapKeyEnemyBarbarian = "barbarian";

Barbarian* Barbarian::deserialize(ValueMap* initProperties)
{
	Barbarian* instance = new Barbarian(initProperties);

	instance->autorelease();

	return instance;
}

Barbarian::Barbarian(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_Enemies_Barbarian_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(278.0f, 288.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Barbarian::~Barbarian()
{
}
