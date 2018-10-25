#pragma once
#include "steam_api.h"

class Steam
{
public:
	static bool isSteamApiAvailable();

	static const int SteamAppId;

private:
	static Steam* getInstance();

	Steam();
	~Steam();

	static Steam* instance;
};
