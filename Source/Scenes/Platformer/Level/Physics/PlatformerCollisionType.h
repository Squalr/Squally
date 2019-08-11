#pragma once

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
	SolidNpcOnly		= 1 << 7,
	Water				= 1 << 8,
	GroundDetector		= 1 << 9,
	WallDetector		= 1 << 10,
	PlayerWeapon		= 1 << 11,
	NpcWeapon			= 1 << 12,
	EnemyWeapon			= 1 << 13,
	Breakable			= 1 << 14,
	Damage				= 1 << 15,
	Collectable			= 1 << 16,
	Trigger				= 1 << 17,

	// Keep in sync with EngineCollisionType:
	Solid				= 1 << 29,
	PassThrough			= 1 << 30,
	Intersection		= 1 << 31,
};