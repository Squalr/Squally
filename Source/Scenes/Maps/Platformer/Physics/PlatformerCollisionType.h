#pragma once

enum class PlatformerCollisionType
{
	None = 0,
	Solid = 1 << 1,
	PassThrough = 1 << 2,
	Player = 1 << 3,
	FriendlyNpc = 1 << 4,
	Enemy = 1 << 5,
	EnemyFlying = 1 << 6,
	Force = 1 << 7,
	SolidNpcOnly = 1 << 8,
	SolidFlyingNpcOnly = 1 << 9,
	Water = 1 << 10,
	Lava = 1 << 11,
	GroundDetector = 1 << 12,
};