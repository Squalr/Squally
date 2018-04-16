#include "EyeScorpion.h"

EyeScorpion* EyeScorpion::create()
{
	EyeScorpion* instance = new EyeScorpion();

	instance->autorelease();

	return instance;
}

EyeScorpion::EyeScorpion() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

EyeScorpion::~EyeScorpion()
{
}
