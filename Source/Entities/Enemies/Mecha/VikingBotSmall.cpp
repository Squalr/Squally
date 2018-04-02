#include "VikingBotSmall.h"

VikingBotSmall* VikingBotSmall::create()
{
	VikingBotSmall* instance = new VikingBotSmall();

	instance->autorelease();

	return instance;
}

VikingBotSmall::VikingBotSmall() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

VikingBotSmall::~VikingBotSmall()
{
}
