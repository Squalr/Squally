#include "VikingBot.h"

VikingBot* VikingBot::create()
{
	VikingBot* instance = new VikingBot();

	instance->autorelease();

	return instance;
}

VikingBot::VikingBot() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

VikingBot::~VikingBot()
{
}
