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
	EnemyFlying			= 1 << 6,
	Force				= 1 << 7,
	SolidNpcOnly		= 1 << 8,
	SolidFlyingNpcOnly	= 1 << 9,
	Water				= 1 << 10,
	GroundDetector		= 1 << 11,
	WallDetector		= 1 << 12,
	PlayerWeapon		= 1 << 13,
	NpcWeapon			= 1 << 14,
	EnemyWeapon			= 1 << 15,
	Breakable			= 1 << 16,
	Damage				= 1 << 17,
	Collectable			= 1 << 18,
	Trigger				= 1 << 19,

	// Keep in sync with EngineCollisionType:
	Solid				= 1 << 29,
	PassThrough			= 1 << 30,
	Intersection		= 1 << 31,
};