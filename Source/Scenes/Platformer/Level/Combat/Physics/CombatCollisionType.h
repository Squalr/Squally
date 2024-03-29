#pragma once

#include "Engine/Physics/EnginePhysicsTypes.h"

enum class CombatCollisionType
{
	None					= 0,
	EntityFriendly			= 1 << 0,
	EntityEnemy				= 1 << 2,
	Projectile				= 1 << 3,
	ProjectileFriendlyOnly	= 1 << 4,
	ProjectileEnemyOnly		= 1 << 5,
	Movement				= 1 << 6,

	KillPlane			= (int)EngineCollisionTypes::KillPlane,
	Solid				= (int)EngineCollisionTypes::Solid,
	PassThrough			= (int)EngineCollisionTypes::PassThrough,
};