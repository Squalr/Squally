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
	HeadDetector		= 1 << 8,
	WallDetector		= 1 << 9,
	PlayerHover			= 1 << 10,
	Hover				= 1 << 11,
	Force				= 1 << 12,
	// Triggers & Walls
	Trigger				= 1 << 13,
	SolidPlayerOnly		= 1 << 14,
	SolidNpcOnly		= 1 << 15,
	// Environment
	Water				= 1 << 16,
	Damage				= 1 << 17,
	// Objects
	Breakable			= 1 << 18,
	Collectable			= 1 << 19,
	Cinematic			= 1 << 20,
	
	// Engine (keep in sync with EngineCollisionTypes)
	KillPlane			= (int)EngineCollisionTypes::KillPlane,
	Solid				= (int)EngineCollisionTypes::Solid,
	SolidRoof			= (int)EngineCollisionTypes::SolidRoof,
	PassThrough			= (int)EngineCollisionTypes::PassThrough,
	Intersection		= (int)EngineCollisionTypes::Intersection,
};