#pragma once

enum class EngineGravityFlags
{
	Default		= 0, // Default category
};

enum class EngineCollisionFlags
{
	Default		= 0, // Default category
};

enum class EnginePhysicsFlags
{
	Default		= 0, // Default category
};

enum class EngineCollisionTypes
{
	None				= 0,
	KillPlane			= 1 << 29,
	Solid				= 1 << 30,
	PassThrough			= 1 << 31,
};