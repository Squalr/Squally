#pragma once

enum class PlatformerCollisionType
{
	None				= 0,
	Physics				= 1 << 0,
	Solid				= 1 << 1,
	PassThrough			= 1 << 2,
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
	Damage				= 1 << 13,
Collectable				= 1 << 14,
};