#include "VikingBotSmall.h"

const std::string VikingBotSmall::MapKeyEnemyVikingBotSmall = "viking_bot_small";

VikingBotSmall* VikingBotSmall::deserialize(ValueMap* initProperties)
{
	VikingBotSmall* instance = new VikingBotSmall(initProperties);

	instance->autorelease();

	return instance;
}

VikingBotSmall::VikingBotSmall(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Mech_Enemies_VikingBotSmall_Animations,
	PlatformerCollisionType::Enemy,
	Size(768.0f, 768.0f),
	0.25f,
	Vec2(0.0f, 160.0f))
{
}

VikingBotSmall::~VikingBotSmall()
{
}
