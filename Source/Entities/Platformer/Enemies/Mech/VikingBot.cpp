#include "VikingBot.h"

const std::string VikingBot::KeyEnemyVikingBot = "viking_bot";

VikingBot* VikingBot::deserialize(ValueMap* initProperties)
{
	VikingBot* instance = new VikingBot(initProperties);

	instance->autorelease();

	return instance;
}

VikingBot::VikingBot(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Mech_VikingBot_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(768.0f, 960.0f),
	0.5f,
	Vec2(-332.0f, 0.0f))
{
}

VikingBot::~VikingBot()
{
}
