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
	// Weapons
	EntityWeapon		= 1 << 4,
	PlayerWeapon		= 1 << 5,
	EnemyWeapon			= 1 << 6,
	// Entity augmentation
	GroundDetector		= 1 << 7,
	JumpDetector		= 1 << 8,
	HeadDetector		= 1 << 9,
	WallDetector		= 1 << 10,
	PlayerHover			= 1 << 11,
	Hover				= 1 << 12,
	Force				= 1 << 13,
	// Triggers & Walls
	Trigger				= 1 << 14,
	SolidPlayerOnly		= 1 << 15,
	SolidNpcOnly		= 1 << 16,
	// Environment
	Water				= 1 << 17,
	Damage				= 1 << 18,
	// Objects
	Breakable			= 1 << 19,
	Collectable			= 1 << 20,
	Cinematic			= 1 << 21,
	
	// Engine (keep in sync with EngineCollisionTypes)
	KillPlane			= (int)EngineCollisionTypes::KillPlane,
	Solid				= (int)EngineCollisionTypes::Solid,
	SolidRoof			= (int)EngineCollisionTypes::SolidRoof,
	PassThrough			= (int)EngineCollisionTypes::PassThrough,
	Intersection		= (int)EngineCollisionTypes::Intersection,
};