#include "VoidDemon.h"

VoidDemon* VoidDemon::create()
{
	VoidDemon* instance = new VoidDemon();

	instance->autorelease();

	return instance;
}

VoidDemon::VoidDemon() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

VoidDemon::~VoidDemon()
{
}
