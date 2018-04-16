#include "DragonDemon.h"

DragonDemon* DragonDemon::create()
{
	DragonDemon* instance = new DragonDemon();

	instance->autorelease();

	return instance;
}

DragonDemon::DragonDemon() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

DragonDemon::~DragonDemon()
{
}
