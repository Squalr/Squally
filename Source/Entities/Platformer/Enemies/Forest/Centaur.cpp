#include "Centaur.h"

const std::string Centaur::MapKeyEnemyCentaur = "centaur";

Centaur* Centaur::deserialize(ValueMap* initProperties)
{
	Centaur* instance = new Centaur(initProperties);

	instance->autorelease();

	return instance;
}

Centaur::Centaur(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Forest_Enemies_Centaur_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(296.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Centaur::~Centaur()
{
}
