#include "FireElemental.h"

const std::string FireElemental::MapKeyEnemyFireElemental = "fire_elemental";

FireElemental* FireElemental::deserialize(ValueMap* initProperties)
{
	FireElemental* instance = new FireElemental(initProperties);

	instance->autorelease();

	return instance;
}

FireElemental::FireElemental(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Volcano_Enemies_FireElemental_Animations,
	PlatformerCollisionType::Enemy,
	Size(820.0f, 1480.0f),
	0.20f,
	Vec2(64.0f, -740.0f))
{
}

FireElemental::~FireElemental()
{
}
