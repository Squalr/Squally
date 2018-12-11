#include "Scarecrow.h"

const std::string Scarecrow::MapKeyEnemyScarecrow = "scarecrow";

Scarecrow* Scarecrow::deserialize(ValueMap* initProperties)
{
	Scarecrow* instance = new Scarecrow(initProperties);

	instance->autorelease();

	return instance;
}

Scarecrow::Scarecrow(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Castle_Enemies_Scarecrow_Animations,
	PlatformerCollisionType::Enemy,
	Size(196.0f, 512.0f),
	0.8f,
	Vec2(0.0f, -128.0f))
{
}

Scarecrow::~Scarecrow()
{
}
