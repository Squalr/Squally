#include "MechGolemDark.h"

const std::string MechGolemDark::KeyEnemyMechGolemDark = "mech_golem_dark";

MechGolemDark* MechGolemDark::create()
{
	MechGolemDark* instance = new MechGolemDark();

	instance->autorelease();

	return instance;
}

MechGolemDark::MechGolemDark() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_MechGolemDark_Animations,
	false,
	Size(460.0f, 512.0f),
	0.4f,
	Vec2(0.0f, -248.0f))
{
}

MechGolemDark::~MechGolemDark()
{
}
