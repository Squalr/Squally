#include "Steam.h"

#include <string>

#include "steam_api.h"

#include "Engine/Utils/LogUtils.h"

using namespace cocos2d;

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

bool Steam::init()
{
	if (Steam::isSquallySteamBuild())
	{
		if (SteamAPI_RestartAppIfNecessary(Steam::SteamAppId))
		{
			return false;
		}

		if (!SteamAPI_Init())
		{
			return false;
		}

		LogUtils::log("Steam initialized");
	}

	return true;
}

bool Steam::isSquallySteamBuild()
{
	// TODO: Make this compiler flag dependent or something
	return true;
}

bool Steam::isCloudSaveAvailable()
{
	if (!Steam::isSquallySteamBuild())
	{
		return false;
	}

	ISteamRemoteStorage* steamRemoteStorage = SteamRemoteStorage();

	if (!steamRemoteStorage->IsCloudEnabledForAccount() || !steamRemoteStorage->IsCloudEnabledForApp())
	{
		return false;
	}

	return true;
}

LanguageType Steam::getLanguage()
{
	if (!Steam::isSquallySteamBuild())
	{
		return LanguageType::ENGLISH;
	}

	ISteamApps* steamApps = SteamApps();

	if (steamApps == nullptr)
	{
		return LanguageType::ENGLISH;
	}

	std::string language = steamApps->GetCurrentGameLanguage();

	if (language == "arabic")
	{
		return LanguageType::ARABIC;
	}
	else if (language == "bulgarian")
	{
		return LanguageType::BULGARIAN;
	}
	else if (language == "schinese")
	{
		return LanguageType::CHINESE_SIMPLIFIED;
	}
	else if (language == "tchinese")
	{
		return LanguageType::CHINESE_TRADITIONAL;
	}
	else if (language == "czech")
	{
		return LanguageType::CZECH;
	}
	else if (language == "danish")
	{
		return LanguageType::DANISH;
	}
	else if (language == "dutch")
	{
		return LanguageType::DUTCH;
	}
	else if (language == "english")
	{
		return LanguageType::ENGLISH;
	}
	else if (language == "finnish")
	{
		return LanguageType::FINNISH;
	}
	else if (language == "french")
	{
		return LanguageType::FRENCH;
	}
	else if (language == "german")
	{
		return LanguageType::GERMAN;
	}
	else if (language == "greek")
	{
		return LanguageType::GREEK;
	}
	else if (language == "hungarian")
	{
		return LanguageType::HUNGARIAN;
	}
	else if (language == "italian")
	{
		return LanguageType::ITALIAN;
	}
	else if (language == "japanese")
	{
		return LanguageType::JAPANESE;
	}
	else if (language == "koreana") // typo in the api
	{
		return LanguageType::KOREAN;
	}
	else if (language == "norwegian")
	{
		return LanguageType::NORWEGIAN;
	}
	else if (language == "polish")
	{
		return LanguageType::POLISH;
	}
	else if (language == "portuguese")
	{
		return LanguageType::PORTUGUESE;
	}
	else if (language == "brazilian")
	{
		return LanguageType::PORTUGUESE_BRAZIL;
	}
	else if (language == "romanian")
	{
		return LanguageType::ROMANIAN;
	}
	else if (language == "russian")
	{
		return LanguageType::RUSSIAN;
	}
	else if (language == "spanish")
	{
		return LanguageType::SPANISH;
	}
	else if (language == "latam")
	{
		return LanguageType::SPANISH_LATIN_AMERICAN;
	}
	else if (language == "swedish")
	{
		return LanguageType::SWEDISH;
	}
	else if (language == "thai")
	{
		return LanguageType::THAI;
	}
	else if (language == "turkish")
	{
		return LanguageType::TURKISH;
	}
	else if (language == "ukrainian")
	{
		return LanguageType::UKRAINIAN;
	}
	else if (language == "vietnamese")
	{
		return LanguageType::VIETNAMESE;
	}

	// Fallback default
	return LanguageType::ENGLISH;
}
