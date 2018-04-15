#include "GoblinShaman.h"

GoblinShaman* GoblinShaman::create()
{
	GoblinShaman* instance = new GoblinShaman();

	instance->autorelease();

	return instance;
}

GoblinShaman::GoblinShaman() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

GoblinShaman::~GoblinShaman()
{
}
