#include "GoblinElf.h"

GoblinElf* GoblinElf::create()
{
	GoblinElf* instance = new GoblinElf();

	instance->autorelease();

	return instance;
}

GoblinElf::GoblinElf() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_GoblinElf_Animations,
	false,
	Size(96.0f, 204.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

GoblinElf::~GoblinElf()
{
}
