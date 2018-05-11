#include "DemonGrunt.h"

DemonGrunt* DemonGrunt::create()
{
	DemonGrunt* instance = new DemonGrunt();

	instance->autorelease();

	return instance;
}

DemonGrunt::DemonGrunt() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_DemonGrunt_Animations,
	false)
{
}

DemonGrunt::~DemonGrunt()
{
}
