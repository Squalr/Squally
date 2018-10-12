#include "Tigress.h"

const std::string Tigress::MapKeyEnemyTigress = "tigress";

Tigress* Tigress::deserialize(ValueMap* initProperties)
{
	Tigress* instance = new Tigress(initProperties);

	instance->autorelease();

	return instance;
}

Tigress::Tigress(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Ruins_Enemies_Tigress_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(128.0f, 256.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Tigress::~Tigress()
{
}
