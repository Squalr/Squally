#include "GoblinGruntBoar.h"

GoblinGruntBoar* GoblinGruntBoar::create()
{
	GoblinGruntBoar* instance = new GoblinGruntBoar();

	instance->autorelease();

	return instance;
}

GoblinGruntBoar::GoblinGruntBoar() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_GoblinGruntBoar_Animations,
	false)
{
}

GoblinGruntBoar::~GoblinGruntBoar()
{
}
