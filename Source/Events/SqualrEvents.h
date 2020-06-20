#pragma once
#include <string>


class SqualrEvents
{
public:
	static const std::string EventProjectileCollided;

	static void TriggerProjectileCollided();
};
