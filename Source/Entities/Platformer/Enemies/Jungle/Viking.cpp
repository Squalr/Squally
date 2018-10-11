#include "Viking.h"

const std::string Viking::KeyEnemyViking = "viking";

Viking* Viking::deserialize(ValueMap* initProperties)
{
	Viking* instance = new Viking(initProperties);

	instance->autorelease();

	return instance;
}

Viking::Viking(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_Enemies_Viking_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(284.0f, 256.0f),
	1.0f,
	Vec2(0.0f, -112.0f))
{
}

Viking::~Viking()
{
}
