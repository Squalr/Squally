#include "GoblinElf.h"

GoblinElf* GoblinElf::create()
{
	GoblinElf* instance = new GoblinElf();

	instance->autorelease();

	return instance;
}

GoblinElf::GoblinElf() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

GoblinElf::~GoblinElf()
{
}
