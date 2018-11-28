#include "Medusa.h"

const std::string Medusa::MapKeyEnemyMedusa = "medusa";

Medusa* Medusa::deserialize(ValueMap* initProperties)
{
	Medusa* instance = new Medusa(initProperties);

	instance->autorelease();

	return instance;
}

Medusa::Medusa(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Ruins_Enemies_Medusa_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(224.0f, 304.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Medusa::~Medusa()
{
}
