#include "EarthGolem.h"

EarthGolem* EarthGolem::create()
{
	EarthGolem* instance = new EarthGolem();

	instance->autorelease();

	return instance;
}

EarthGolem::EarthGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

EarthGolem::~EarthGolem()
{
}
