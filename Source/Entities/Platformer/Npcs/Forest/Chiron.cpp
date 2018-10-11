#include "CastleGuard.h"

const std::string CastleGuard::KeyEnemyCastleGuard = "CastleGuard";

CastleGuard* CastleGuard::deserialize(ValueMap* initProperties)
{
	CastleGuard* instance = new CastleGuard(initProperties);

	instance->autorelease();

	return instance;
}

CastleGuard::CastleGuard(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Npcs_Guard_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

CastleGuard::~CastleGuard()
{
}
