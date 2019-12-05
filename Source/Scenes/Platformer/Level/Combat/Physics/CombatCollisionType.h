#pragma once

#include "Engine/Physics/EngineCollisionTypes.h"

enum class CombatCollisionType
{
	None					= 0,
	EntityFriendly			= 1 << 0,
	EntityEnemy				= 1 << 2,
	Projectile				= 1 << 3,
	ProjectileFriendlyOnly	= 1 << 4,
	ProjectileEnemyOnly		= 1 << 5,

	KillPlane			= (int)EngineCollisionTypes::KillPlane,
	Solid				= (int)EngineCollisionTypes::Solid,
	SolidRoof			= (int)EngineCollisionTypes::SolidRoof,
	PassThrough			= (int)EngineCollisionTypes::PassThrough,
	Intersection		= (int)EngineCollisionTypes::Intersection,
};