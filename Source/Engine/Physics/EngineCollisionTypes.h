#pragma once

enum class EngineCollisionTypes
{
	None				= 0,
	KillPlane			= 1 << 27,
	Solid				= 1 << 28,
	SolidRoof			= 1 << 29,
	PassThrough			= 1 << 30,
	Intersection		= 1 << 31,
};