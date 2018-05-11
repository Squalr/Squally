#include "MechGolemDark.h"

MechGolemDark* MechGolemDark::create()
{
	MechGolemDark* instance = new MechGolemDark();

	instance->autorelease();

	return instance;
}

MechGolemDark::MechGolemDark() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_MechGolemDark_Animations,
	false)
{
}

MechGolemDark::~MechGolemDark()
{
}
