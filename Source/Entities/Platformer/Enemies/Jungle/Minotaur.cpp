#include "Minotaur.h"

const std::string Minotaur::MapKeyEnemyMinotaur = "minotaur";

Minotaur* Minotaur::deserialize(ValueMap* initProperties)
{
	Minotaur* instance = new Minotaur(initProperties);

	instance->autorelease();

	return instance;
}

Minotaur::Minotaur(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Jungle_Enemies_Minotaur_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(278.0f, 288.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Minotaur::~Minotaur()
{
}
