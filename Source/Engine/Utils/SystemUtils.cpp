#include "SystemUtils.h"

#include "Engine/Steam/Steam.h"

std::string SystemUtils::GetUniqueSystemIdentifier()
{
	const std::string steamId = Steam::GetSteamUserId();

	if (!steamId.empty())
	{
		return steamId;
	}

	return "<no-unique-id>";
}
