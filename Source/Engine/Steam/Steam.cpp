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

bool Steam::isSteamEnabled()
{
	// TODO: Make this compiler flag dependent or something
	return true;
}

bool Steam::isCloudSaveAvailable()
{
	ISteamRemoteStorage* steamRemoteStorage = SteamRemoteStorage();

	if (!Steam::isSteamEnabled() || !steamRemoteStorage->IsCloudEnabledForAccount() || !steamRemoteStorage->IsCloudEnabledForApp())
	{
		return false;
	}

	return true;
}
