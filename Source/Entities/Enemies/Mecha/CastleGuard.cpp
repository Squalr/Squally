#include "CastleGuard.h"

CastleGuard* CastleGuard::create()
{
	CastleGuard* instance = new CastleGuard();

	instance->autorelease();

	return instance;
}

CastleGuard::CastleGuard() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

CastleGuard::~CastleGuard()
{
}
