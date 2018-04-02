#include "CastleGuard.h"

CastleGuard* CastleGuard::create()
{
	CastleGuard* instance = new CastleGuard();

	instance->autorelease();

	return instance;
}

CastleGuard::CastleGuard() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

CastleGuard::~CastleGuard()
{
}
