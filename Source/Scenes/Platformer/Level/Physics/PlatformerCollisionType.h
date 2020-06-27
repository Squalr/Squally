#pragma once

#include "Engine/Physics/EngineCollisionTypes.h"

enum class PlatformerCollisionType
{
	None				= 0,
	Physics				= 1 << 0,
	// Entities
	Entity				= 1 << 1,
	Player				= 1 << 2,
	Enemy				= 1 << 3,
	EntityMovement		= 1 << 4,
	PlayerMovement		= 1 << 5,
	EnemyMovement		= 1 << 6,
	// Weapons
	EntityWeapon		= 1 << 7,
	PlayerWeapon		= 1 << 8,
	EnemyWeapon			= 1 << 9,
	// Entity augmentation
	GroundDetector		= 1 << 10,
	JumpDetector		= 1 << 11,
	HeadDetector		= 1 << 12,
	WallDetector		= 1 << 13,
	Hover				= 1 << 14,
	// PlayerHover			= 1 << 15, // Disabled, as Hover covers this. No other entity hovers yet.
	Force				= 1 << 16,
	// Triggers & Walls
	Trigger				= 1 << 17,
	SolidPlayerOnly		= 1 << 18,
	SolidNpcOnly		= 1 << 19,
	// Environment
	Water				= 1 << 20,
	Damage				= 1 << 21,
	// Objects
	Breakable			= 1 << 22,
	Collectable			= 1 << 23,
	Cinematic			= 1 << 24,
	
	// Engine (keep in sync with EngineCollisionTypes)
	KillPlane			= (int)EngineCollisionTypes::KillPlane,
	Solid				= (int)EngineCollisionTypes::Solid,
	SolidRoof			= (int)EngineCollisionTypes::SolidRoof,
	PassThrough			= (int)EngineCollisionTypes::PassThrough,
	Intersection		= (int)EngineCollisionTypes::Intersection,
};