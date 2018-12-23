#include "Localization.h"

#include "cocos/platform/CCApplication.h"
#include "cocos/platform/CCFileUtils.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Steam/Steam.h"

#include "Resources/FontResources.h"
#include "Resources/StringResources.h"

using namespace cocos2d;

Localization* Localization::instance = nullptr;

Localization* Localization::getInstance()
{
	if (Localization::instance == nullptr)
	{
		Localization::instance = new Localization();
	}

	return Localization::instance;
}

Localization::Localization()
{
}

Localization::~Localization()
{
}

cocos2d::LanguageType Localization::getLanguage()
{
	// Saved language in config file has priority
	if (ConfigManager::hasLanguageSaved())
	{
		std::string languageCode = ConfigManager::getLanguage();

	}

	// Otherwise take the native language (Steam > System in priority)
	return Localization::getNativeLanguage();
}

void Localization::setLanguage(cocos2d::LanguageType languageType)
{
	ConfigManager::setLanguage(Localization::languageTypeToLanguageCode(languageType));
	ConfigManager::save();

	LocalizationEvents::TriggerLocaleChange(LocalizationEvents::LocaleChangeArgs(languageType));
}

cocos2d::LanguageType Localization::getNativeLanguage()
{
	// Default to steam language
	if (Steam::isSquallySteamBuild())
	{
		return Steam::getLanguage();
	}

	// Steam not available -- use system language
	return Application::getInstance()->getCurrentLanguage();
}

std::string Localization::getLanguageCode()
{
	// TEMP!
	return "en";

	return Localization::languageTypeToLanguageCode(Localization::getLanguage());
}

std::string Localization::getPixelFont()
{
	switch (Application::getInstance()->getCurrentLanguage())
	{
		default:
		case LanguageType::ENGLISH:
		case LanguageType::CHINESE_SIMPLIFIED:
		case LanguageType::CHINESE_TRADITIONAL:
		case LanguageType::JAPANESE:
		case LanguageType::KOREAN:
		{
			return FontResources::Pixel_Zpix;
		}
		case LanguageType::ARABIC:
		case LanguageType::BULGARIAN:
		case LanguageType::CZECH:
		case LanguageType::DANISH:
		case LanguageType::DUTCH:
		case LanguageType::FINNISH:
		case LanguageType::FRENCH:
		case LanguageType::GERMAN:
		case LanguageType::GREEK:
		case LanguageType::HUNGARIAN:
		case LanguageType::ITALIAN:
		case LanguageType::NORWEGIAN:
		case LanguageType::POLISH:
		case LanguageType::PORTUGUESE:
		case LanguageType::PORTUGUESE_BRAZIL:
		case LanguageType::ROMANIAN:
		case LanguageType::RUSSIAN:
		case LanguageType::SPANISH:
		case LanguageType::SPANISH_LATIN_AMERICAN:
		case LanguageType::SWEDISH:
		case LanguageType::THAI:
		case LanguageType::TURKISH:
		case LanguageType::UKRAINIAN:
		case LanguageType::VIETNAMESE:
		{
			// TODO
			return FontResources::Pixel_Zpix;
		}
	}
}

std::string Localization::getMainFont()
{
	switch (Application::getInstance()->getCurrentLanguage())
	{
		default:
		case LanguageType::ENGLISH:
		{
			return FontResources::Montserrat_Medium;
		}
		case LanguageType::CHINESE_SIMPLIFIED:
		case LanguageType::CHINESE_TRADITIONAL:
		case LanguageType::JAPANESE:
		case LanguageType::KOREAN:
		case LanguageType::ARABIC:
		case LanguageType::BULGARIAN:
		case LanguageType::CZECH:
		case LanguageType::DANISH:
		case LanguageType::DUTCH:
		case LanguageType::FINNISH:
		case LanguageType::FRENCH:
		case LanguageType::GERMAN:
		case LanguageType::GREEK:
		case LanguageType::HUNGARIAN:
		case LanguageType::ITALIAN:
		case LanguageType::NORWEGIAN:
		case LanguageType::POLISH:
		case LanguageType::PORTUGUESE:
		case LanguageType::PORTUGUESE_BRAZIL:
		case LanguageType::ROMANIAN:
		case LanguageType::RUSSIAN:
		case LanguageType::SPANISH:
		case LanguageType::SPANISH_LATIN_AMERICAN:
		case LanguageType::SWEDISH:
		case LanguageType::THAI:
		case LanguageType::TURKISH:
		case LanguageType::UKRAINIAN:
		case LanguageType::VIETNAMESE:
		{
			// TODO
			return FontResources::Montserrat_Medium;
		}
	}
}

std::string Localization::getCodingFont()
{
	switch (Application::getInstance()->getCurrentLanguage())
	{
		default:
		case LanguageType::ENGLISH:
		{
			return FontResources::UbuntuMono_Bold;
		}
		case LanguageType::CHINESE_SIMPLIFIED:
		case LanguageType::CHINESE_TRADITIONAL:
		case LanguageType::JAPANESE:
		case LanguageType::KOREAN:
		{
			return FontResources::Ubuntu_WenQuanYiMicroHeiMono_02;
		}
		case LanguageType::ARABIC:
		case LanguageType::BULGARIAN:
		case LanguageType::CZECH:
		case LanguageType::DANISH:
		case LanguageType::DUTCH:
		case LanguageType::FINNISH:
		case LanguageType::FRENCH:
		case LanguageType::GERMAN:
		case LanguageType::GREEK:
		case LanguageType::HUNGARIAN:
		case LanguageType::ITALIAN:
		case LanguageType::NORWEGIAN:
		case LanguageType::POLISH:
		case LanguageType::PORTUGUESE:
		case LanguageType::PORTUGUESE_BRAZIL:
		case LanguageType::ROMANIAN:
		case LanguageType::RUSSIAN:
		case LanguageType::SPANISH:
		case LanguageType::SPANISH_LATIN_AMERICAN:
		case LanguageType::SWEDISH:
		case LanguageType::THAI:
		case LanguageType::TURKISH:
		case LanguageType::UKRAINIAN:
		case LanguageType::VIETNAMESE:
		{
			// TODO
			return FontResources::UbuntuMono_Bold;
		}
	}
}

float Localization::getFontSizeH1(std::string fontResource)
{
	return 32.0f;
}

float Localization::getFontSizeH2(std::string fontResource)
{
	return 28.0f;
}

float Localization::getFontSizeH3(std::string fontResource)
{
	return 24.0f;
}

float Localization::getFontSizeP(std::string fontResource)
{
	return 20.0f;
}

cocos2d::LanguageType Localization::languageCodeToLanguageType(std::string languageCode)
{
	if (languageCode == "ar")
	{
		return LanguageType::ARABIC;
	}
	else if (languageCode == "bg")
	{
		return LanguageType::BULGARIAN;
	}
	else if (languageCode == "zh-CN")
	{
		return LanguageType::CHINESE_SIMPLIFIED;
	}
	else if (languageCode == "zh-TW")
	{
		return LanguageType::CHINESE_TRADITIONAL;
	}
	else if (languageCode == "cs")
	{
		return LanguageType::CZECH;
	}
	else if (languageCode == "da")
	{
		return LanguageType::DANISH;
	}
	else if (languageCode == "nl")
	{
		return LanguageType::DUTCH;
	}
	else if (languageCode == "en")
	{
		return LanguageType::ENGLISH;
	}
	else if (languageCode == "fi")
	{
		return LanguageType::FINNISH;
	}
	else if (languageCode == "fr")
	{
		return LanguageType::FRENCH;
	}
	else if (languageCode == "de")
	{
		return LanguageType::GERMAN;
	}
	else if (languageCode == "el")
	{
		return LanguageType::GREEK;
	}
	else if (languageCode == "hu")
	{
		return LanguageType::HUNGARIAN;
	}
	else if (languageCode == "it")
	{
		return LanguageType::ITALIAN;
	}
	else if (languageCode == "ja")
	{
		return LanguageType::JAPANESE;
	}
	else if (languageCode == "ko")
	{
		return LanguageType::KOREAN;
	}
	else if (languageCode == "no")
	{
		return LanguageType::NORWEGIAN;
	}
	else if (languageCode == "pl")
	{
		return LanguageType::POLISH;
	}
	else if (languageCode == "pt")
	{
		return LanguageType::PORTUGUESE;
	}
	else if (languageCode == "pt-BR")
	{
		return LanguageType::PORTUGUESE_BRAZIL;
	}
	else if (languageCode == "ro")
	{
		return LanguageType::ROMANIAN;
	}
	else if (languageCode == "ru")
	{
		return LanguageType::RUSSIAN;
	}
	else if (languageCode == "es")
	{
		return LanguageType::SPANISH;
	}
	else if (languageCode == "es-419")
	{
		return LanguageType::SPANISH_LATIN_AMERICAN;
	}
	else if (languageCode == "sv")
	{
		return LanguageType::SWEDISH;
	}
	else if (languageCode == "th")
	{
		return LanguageType::THAI;
	}
	else if (languageCode == "tr")
	{
		return LanguageType::TURKISH;
	}
	else if (languageCode == "uk")
	{
		return LanguageType::UKRAINIAN;
	}
	else if (languageCode == "vn")
	{
		return LanguageType::VIETNAMESE;
	}

	// Default
	return LanguageType::ENGLISH;
}

std::string Localization::languageTypeToLanguageCode(cocos2d::LanguageType languageType)
{
	switch (languageType)
	{
		case LanguageType::ARABIC:
		{
			return "ar";
		}
		case LanguageType::BULGARIAN:
		{
			return "bg";
		}
		case LanguageType::CHINESE_SIMPLIFIED:
		{
			return "zh-CN";
		}
		case LanguageType::CHINESE_TRADITIONAL:
		{
			return "zh-TW";
		}
		case LanguageType::CZECH:
		{
			return "cs";
		}
		case LanguageType::DANISH:
		{
			return "da";
		}
		case LanguageType::DUTCH:
		{
			return "nl";
		}
		case LanguageType::FINNISH:
		{
			return "fi";
		}
		case LanguageType::FRENCH:
		{
			return "fr";
		}
		case LanguageType::GERMAN:
		{
			return "de";
		}
		case LanguageType::GREEK:
		{
			return "el";
		}
		case LanguageType::HUNGARIAN:
		{
			return "hu";
		}
		case LanguageType::ITALIAN:
		{
			return "it";
		}
		case LanguageType::JAPANESE:
		{
			return "ja";
		}
		case LanguageType::KOREAN:
		{
			return "ko";
		}
		case LanguageType::NORWEGIAN:
		{
			return "no";
		}
		case LanguageType::POLISH:
		{
			return "pl";
		}
		case LanguageType::PORTUGUESE:
		{
			return "pt";
		}
		case LanguageType::PORTUGUESE_BRAZIL:
		{
			return "pt-BR";
		}
		case LanguageType::ROMANIAN:
		{
			return "ro";
		}
		case LanguageType::RUSSIAN:
		{
			return "ru";
		}
		case LanguageType::SPANISH:
		{
			return "es";
		}
		case LanguageType::SPANISH_LATIN_AMERICAN:
		{
			return "es-419";
		}
		case LanguageType::SWEDISH:
		{
			return "sv";
		}
		case LanguageType::THAI:
		{
			return "th";
		}
		case LanguageType::TURKISH:
		{
			return "tr";
		}
		case LanguageType::UKRAINIAN:
		{
			return "uk";
		}
		case LanguageType::VIETNAMESE:
		{
			return "vn";
		}
		case LanguageType::ENGLISH:
		default:
		{
			return "en";
		}
	}
}
