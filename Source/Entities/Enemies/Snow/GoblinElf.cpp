#include "GoblinElf.h"

const std::string GoblinElf::KeyEnemyGoblinElf = "goblin_elf";

GoblinElf* GoblinElf::deserialize(ValueMap* initProperties)
{
	GoblinElf* instance = new GoblinElf(initProperties);

	instance->autorelease();

	return instance;
}

GoblinElf::GoblinElf(ValueMap* initProperties) : Enemy(initProperties,
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
