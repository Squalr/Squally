#pragma once

enum class EngineCollisionTypes
{
	None				= 0,
	Solid				= 1 << 28,
	SolidRoof			= 1 << 29,
	PassThrough			= 1 << 30,
	Intersection		= 1 << 31,
};