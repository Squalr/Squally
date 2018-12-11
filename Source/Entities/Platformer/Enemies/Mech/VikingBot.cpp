#include "VikingBot.h"

const std::string VikingBot::MapKeyEnemyVikingBot = "viking_bot";

VikingBot* VikingBot::deserialize(ValueMap* initProperties)
{
	VikingBot* instance = new VikingBot(initProperties);

	instance->autorelease();

	return instance;
}

VikingBot::VikingBot(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Mech_Enemies_VikingBot_Animations,
	PlatformerCollisionType::Enemy,
	Size(768.0f, 960.0f),
	0.5f,
	Vec2(-332.0f, 0.0f))
{
}

VikingBot::~VikingBot()
{
}
