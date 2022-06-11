#pragma once

enum class EngineCollisionTypes
{
	None				= 0,
	KillPlane			= 1 << 28,
	Solid				= 1 << 29,
	SolidRoof			= 1 << 30,
	PassThrough			= 1 << 31,
};