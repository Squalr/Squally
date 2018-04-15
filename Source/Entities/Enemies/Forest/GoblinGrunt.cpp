#include "GoblinGrunt.h"

GoblinGrunt* GoblinGrunt::create()
{
	GoblinGrunt* instance = new GoblinGrunt();

	instance->autorelease();

	return instance;
}

GoblinGrunt::GoblinGrunt() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

GoblinGrunt::~GoblinGrunt()
{
}
