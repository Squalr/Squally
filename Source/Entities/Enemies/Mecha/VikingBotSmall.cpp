#include "VikingBotSmall.h"

VikingBotSmall* VikingBotSmall::create()
{
	VikingBotSmall* instance = new VikingBotSmall();

	instance->autorelease();

	return instance;
}

VikingBotSmall::VikingBotSmall() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

VikingBotSmall::~VikingBotSmall()
{
}
