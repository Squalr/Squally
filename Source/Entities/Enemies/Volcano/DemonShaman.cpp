#include "DemonShaman.h"

DemonShaman* DemonShaman::create()
{
	DemonShaman* instance = new DemonShaman();

	instance->autorelease();

	return instance;
}

DemonShaman::DemonShaman() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

DemonShaman::~DemonShaman()
{
}
