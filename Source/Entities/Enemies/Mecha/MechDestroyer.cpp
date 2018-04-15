#include "MechDestroyer.h"

MechDestroyer* MechDestroyer::create()
{
	MechDestroyer* instance = new MechDestroyer();

	instance->autorelease();

	return instance;
}

MechDestroyer::MechDestroyer() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

MechDestroyer::~MechDestroyer()
{
}
