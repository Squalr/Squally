#include "PenguinGrunt.h"

const std::string PenguinGrunt::MapKeyEnemyPenguinGrunt = "penguin_grunt";

PenguinGrunt* PenguinGrunt::deserialize(ValueMap* initProperties)
{
	PenguinGrunt* instance = new PenguinGrunt(initProperties);

	instance->autorelease();

	return instance;
}

PenguinGrunt::PenguinGrunt(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Snow_Enemies_PenguinGrunt_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(212.0f, 296.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

PenguinGrunt::~PenguinGrunt()
{
}
