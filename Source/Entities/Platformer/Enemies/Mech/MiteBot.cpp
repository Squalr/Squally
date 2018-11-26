#include "MiteBot.h"

const std::string MiteBot::MapKeyEnemyMiteBot = "mite_bot";

MiteBot* MiteBot::deserialize(ValueMap* initProperties)
{
	MiteBot* instance = new MiteBot(initProperties);

	instance->autorelease();

	return instance;
}

MiteBot::MiteBot(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Mech_Enemies_MiteBot_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(420.0f, 296.0f),
	0.4f,
	Vec2(0.0f, 24.0f))
{
}

MiteBot::~MiteBot()
{
}
