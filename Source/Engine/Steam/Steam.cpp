#include "Steam.h"

const int Steam::SteamAppId = 770200;

Steam* Steam::instance = nullptr;

Steam* Steam::getInstance()
{
	if (Steam::instance == nullptr)
	{
		Steam::instance = new Steam();
	}

	return Steam::instance;
}

Steam::Steam()
{
}

Steam::~Steam()
{
}

bool Steam::isSteamApiAvailable()
{
	return true;
}
