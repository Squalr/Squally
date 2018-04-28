#include "GoblinGrunt.h"

GoblinGrunt* GoblinGrunt::create()
{
	GoblinGrunt* instance = new GoblinGrunt();

	instance->autorelease();

	return instance;
}

GoblinGrunt::GoblinGrunt() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

GoblinGrunt::~GoblinGrunt()
{
}
