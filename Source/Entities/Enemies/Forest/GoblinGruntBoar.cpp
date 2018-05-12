#include "GoblinGruntBoar.h"

GoblinGruntBoar* GoblinGruntBoar::create()
{
	GoblinGruntBoar* instance = new GoblinGruntBoar();

	instance->autorelease();

	return instance;
}

GoblinGruntBoar::GoblinGruntBoar() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_GoblinGruntBoar_Animations,
	false,
	Size(128.0f, 296.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

GoblinGruntBoar::~GoblinGruntBoar()
{
}
