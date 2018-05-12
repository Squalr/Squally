#include "DemonGrunt.h"

DemonGrunt* DemonGrunt::create()
{
	DemonGrunt* instance = new DemonGrunt();

	instance->autorelease();

	return instance;
}

DemonGrunt::DemonGrunt() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_DemonGrunt_Animations,
	false,
	Size(312.0f, 372.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

DemonGrunt::~DemonGrunt()
{
}
