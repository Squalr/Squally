#include "GoblinElf.h"

const std::string GoblinElf::KeyEnemyGoblinElf = "goblin_elf";

GoblinElf* GoblinElf::create()
{
	GoblinElf* instance = new GoblinElf();

	instance->autorelease();

	return instance;
}

GoblinElf::GoblinElf() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_GoblinElf_Animations,
	false,
	Size(140.0f, 296.0f),
	0.6f,
	Vec2(0.0f, 0.0f))
{
}

GoblinElf::~GoblinElf()
{
}
