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
	Enemy				= 1 << 5,
	Force				= 1 << 6,
	SolidPlayerOnly		= 1 << 7,
	SolidNpcOnly		= 1 << 8,
	Water				= 1 << 9,
	GroundDetector		= 1 << 10,
	WallDetector		= 1 << 11,
	PlayerWeapon		= 1 << 12,
	NpcWeapon			= 1 << 13,
	EnemyWeapon			= 1 << 14,
	Breakable			= 1 << 15,
	Damage				= 1 << 16,
	Collectable			= 1 << 17,
	Trigger				= 1 << 18,

	Solid				= (int)EngineCollisionTypes::Solid,
	PassThrough			= (int)EngineCollisionTypes::PassThrough,
	Intersection		= (int)EngineCollisionTypes::Intersection,
};