#include "Exterminator.h"

const std::string Exterminator::MapKeyEnemyExterminator = "exterminator";

Exterminator* Exterminator::deserialize(ValueMap* initProperties)
{
	Exterminator* instance = new Exterminator(initProperties);

	instance->autorelease();

	return instance;
}

Exterminator::Exterminator(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Mech_Enemies_Exterminator_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(320.0f, 278.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Exterminator::~Exterminator()
{
}
