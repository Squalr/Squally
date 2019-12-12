#pragma once

#include "Engine/Physics/EngineCollisionTypes.h"

enum class PlatformerCollisionType
{
	None				= 0,
	Physics				= 1 << 0,
	Movement			= 1 << 1,
	Player				= 1 << 2,
	PlayerMovement		= 1 << 3,
	FriendlyNpc			= 1 << 4,
	Helper				= 1 << 5,
	Enemy				= 1 << 6,
	Force				= 1 << 7,
	SolidPlayerOnly		= 1 << 8,
	SolidNpcOnly		= 1 << 9,
	Water				= 1 << 10,
	GroundDetector		= 1 << 11,
	HeadDetector		= 1 << 12,
	WallDetector		= 1 << 13,
	PlayerWeapon		= 1 << 14,
	NpcWeapon			= 1 << 15,
	EnemyWeapon			= 1 << 16,
	Breakable			= 1 << 17,
	Damage				= 1 << 18,
	Collectable			= 1 << 19,
	Trigger				= 1 << 20,

	KillPlane			= (int)EngineCollisionTypes::KillPlane,
	Solid				= (int)EngineCollisionTypes::Solid,
	SolidRoof			= (int)EngineCollisionTypes::SolidRoof,
	PassThrough			= (int)EngineCollisionTypes::PassThrough,
	Intersection		= (int)EngineCollisionTypes::Intersection,
};