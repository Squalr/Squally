#include "BlackWidow.h"

BlackWidow* BlackWidow::create()
{
	BlackWidow* instance = new BlackWidow();

	instance->autorelease();

	return instance;
}

BlackWidow::BlackWidow() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

BlackWidow::~BlackWidow()
{
}
