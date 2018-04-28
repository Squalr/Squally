#include "CastleGuard.h"

CastleGuard* CastleGuard::create()
{
	CastleGuard* instance = new CastleGuard();

	instance->autorelease();

	return instance;
}

CastleGuard::CastleGuard() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

CastleGuard::~CastleGuard()
{
}
