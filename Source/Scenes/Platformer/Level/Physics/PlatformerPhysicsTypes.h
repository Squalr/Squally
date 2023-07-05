#pragma once

#include "Engine/Physics/EnginePhysicsTypes.h"

enum class GravityFlags
{
	Default		= (int)EngineGravityFlags::Default,

	// Start from 1 due to reserved engine types
	Movement	= 1,
	Hover		= 2,
	IsAlive		= 3,
	IsMounted	= 4,
};

enum class CollisionFlags
{
	Default		= (int)EngineCollisionFlags::Default,
	
	// Start from 1 due to reserved engine types
};

enum class PhysicsFlags
{
	Default		= (int)EnginePhysicsFlags::Default,

	// Start from 1 due to reserved engine types
	Movement	= 1,
	IsAlive		= 2,
	IsMounted	= 3,
};

enum class PlatformerCollisionType
{
	None				= 0,
	Physics				= 1 << 0,
	// Entities
	Entity				= 1 << 1,
	Player				= 1 << 2,
	Helper				= 1 << 3,
	Enemy				= 1 << 4,
	EntityMovement		= 1 << 5,
	PlayerMovement		= 1 << 6,
	EnemyMovement		= 1 << 7,
	// Weapons
	EntityWeapon		= 1 << 8,
	PlayerWeapon		= 1 << 9,
	EnemyWeapon			= 1 << 10,
	// Entity augmentation
	GroundDetector		= 1 << 11,
	HeadDetector		= 1 << 12,
	WallDetector		= 1 << 13,
	Hover				= 1 << 14,
	Force				= 1 << 15,
	// Triggers & Walls
	Trigger				= 1 << 16,
	SolidPlayerOnly		= 1 << 17,
	SolidNpcOnly		= 1 << 18,
	// Environment
	Water				= 1 << 19,
	Damage				= 1 << 20,
	// Objects
	Breakable			= 1 << 21,
	Collectable			= 1 << 22,
	Cinematic			= 1 << 23,
	CartStop			= 1 << 24,
	
	// WARNING: Max is 27  due to 28-31 reserved by engine
	
	// Engine (keep in sync with EngineCollisionTypes)
	KillPlane			= (int)EngineCollisionTypes::KillPlane,
	Solid				= (int)EngineCollisionTypes::Solid,
	PassThrough			= (int)EngineCollisionTypes::PassThrough,
};