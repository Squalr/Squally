#include "GoblinGrunt.h"

GoblinGrunt* GoblinGrunt::create()
{
	GoblinGrunt* instance = new GoblinGrunt();

	instance->autorelease();

	return instance;
}

GoblinGrunt::GoblinGrunt() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_GoblinGrunt_Animations,
	false)
{
}

GoblinGrunt::~GoblinGrunt()
{
}
