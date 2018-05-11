#include "GoblinSwordsman.h"

GoblinSwordsman* GoblinSwordsman::create()
{
	GoblinSwordsman* instance = new GoblinSwordsman();

	instance->autorelease();

	return instance;
}

GoblinSwordsman::GoblinSwordsman() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_GoblinSwordsman_Animations,
	false)
{
}

GoblinSwordsman::~GoblinSwordsman()
{
}
