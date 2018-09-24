#include "VikingBotSmall.h"

const std::string VikingBotSmall::KeyEnemyVikingBotSmall = "viking_bot_small";

VikingBotSmall* VikingBotSmall::deserialize(ValueMap* initProperties)
{
	VikingBotSmall* instance = new VikingBotSmall(initProperties);

	instance->autorelease();

	return instance;
}

VikingBotSmall::VikingBotSmall(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Mech_Enemies_VikingBotSmall_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(768.0f, 768.0f),
	0.25f,
	Vec2(0.0f, 160.0f))
{
}

VikingBotSmall::~VikingBotSmall()
{
}
