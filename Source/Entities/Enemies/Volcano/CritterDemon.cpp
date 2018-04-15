#include "CritterDemon.h"

CritterDemon* CritterDemon::create()
{
	CritterDemon* instance = new CritterDemon();

	instance->autorelease();

	return instance;
}

CritterDemon::CritterDemon() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

CritterDemon::~CritterDemon()
{
}
