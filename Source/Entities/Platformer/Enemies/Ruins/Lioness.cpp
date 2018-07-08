#include "Lioness.h"

const std::string Lioness::KeyEnemyLioness = "lioness";

Lioness* Lioness::deserialize(ValueMap* initProperties)
{
	Lioness* instance = new Lioness(initProperties);

	instance->autorelease();

	return instance;
}

Lioness::Lioness(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Ruins_Lioness_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(128.0f, 278.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Lioness::~Lioness()
{
}
