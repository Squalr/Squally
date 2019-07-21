#pragma once

enum class PlatformerCollisionType
{
	None				= 0,
	Physics				= 1 << 0,
	PassThrough			= 1 << 1,
	Entity				= 1 << 2,
	Player				= 1 << 3,
	PlayerHover			= 1 << 4,
	FriendlyNpc			= 1 << 5,
	Enemy				= 1 << 6,
	EnemyFlying			= 1 << 7,
	Force				= 1 << 8,
	SolidNpcOnly		= 1 << 9,
	SolidFlyingNpcOnly	= 1 << 10,
	Water				= 1 << 11,
	GroundDetector		= 1 << 12,
	WallDetector		= 1 << 13,
	PlayerWeapon		= 1 << 14,
	EnemyWeapon			= 1 << 15,
	Breakable			= 1 << 16,
	Damage				= 1 << 17,
	Collectable			= 1 << 18,
	Trigger				= 1 << 19,

	// Keep in sync with EngineCollisionType:
	Solid				= 1 << 30,
	Intersection		= 1 << 31,
};