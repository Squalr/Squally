#include "GoblinGrunt.h"

GoblinGrunt* GoblinGrunt::create()
{
	GoblinGrunt* instance = new GoblinGrunt();

	instance->autorelease();

	return instance;
}

GoblinGrunt::GoblinGrunt() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_GoblinGrunt_Animations,
	false,
	Size(312.0f, 512.0f),
	0.35f,
	Vec2(0.0f, -224.0f))
{
}

GoblinGrunt::~GoblinGrunt()
{
}
