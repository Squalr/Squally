#include "CritterDemon.h"

const std::string CritterDemon::KeyEnemyCritterDemon = "critter_demon";

CritterDemon* CritterDemon::create()
{
	CritterDemon* instance = new CritterDemon();

	instance->autorelease();

	return instance;
}

CritterDemon::CritterDemon() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_CritterDemon_Animations,
	false,
	Size(188.0f, 160.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

CritterDemon::~CritterDemon()
{
}
