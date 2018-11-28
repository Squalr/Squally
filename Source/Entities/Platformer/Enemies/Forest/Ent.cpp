#include "Ent.h"

const std::string Ent::MapKeyEnemyEnt = "ent";

Ent* Ent::deserialize(ValueMap* initProperties)
{
	Ent* instance = new Ent(initProperties);

	instance->autorelease();

	return instance;
}

Ent::Ent(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Forest_Enemies_Ent_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(512.0f, 960.0f),
	0.3f,
	Vec2(24.0f, -452.0f))
{
}

Ent::~Ent()
{
}
