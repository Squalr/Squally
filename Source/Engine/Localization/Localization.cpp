#include "Localization.h"

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
	std::string localizedStringsJson = FileUtils::getInstance()->getStringFromFile(Resources::Strings_Menus.c_str());

	this->localizationMap = new Document();
	this->localizationMap->Parse<0>(localizedStringsJson.c_str());
}

Localization::~Localization()
{
	delete(this->localizationMap);
}

std::string Localization::resolveFile(std::string fileEn)
{
	std::string fileBase = fileEn.substr(0, fileEn.length() - 2);
	Localization* localization = Localization::getInstance();
	std::string languageCode = localization->getLanguageCode();

	return fileBase + languageCode;
}

std::string Localization::resolveString(std::string resourceKey)
{
	Localization* localization = Localization::getInstance();
	std::string languageCode = Localization::getLanguageCode();

	if (localization->localizationMap->HasMember(resourceKey.c_str()))
	{
		auto node = (*localization->localizationMap)[resourceKey.c_str()].GetObjectW();
		if (node.HasMember(languageCode.c_str()))
		{
			return node[languageCode.c_str()].GetString();
		}

		if (node.HasMember("en"))
		{
			CCLOG(("Localization resource key not found: " + resourceKey + " for language code: " + languageCode).c_str());
			CCLOG("Falling back on EN");
			return node["en"].GetString();
		}
	}

	CCLOG(("Localization resource key not found: " + resourceKey).c_str());
	return resourceKey;
}

std::string Localization::getLanguageCode()
{
	switch (Application::getInstance()->getCurrentLanguage())
	{
	case LanguageType::ARABIC:
		return "ar";
	case LanguageType::BULGARIAN:
		return "bg";
	case LanguageType::CHINESE_SIMPLIFIED:
		return "zh-CN";
	case LanguageType::CHINESE_TRADITIONAL:
		return "zh-TW";
	case LanguageType::CZECH:
		return "cs";
	case LanguageType::DANISH:
		return "da";
	case LanguageType::DUTCH:
		return "nl";
	case LanguageType::FINNISH:
		return "fi";
	case LanguageType::FRENCH:
		return "fr";
	case LanguageType::GERMAN:
		return "de";
	case LanguageType::GREEK:
		return "el";
	case LanguageType::HUNGARIAN:
		return "hu";
	case LanguageType::ITALIAN:
		return "it";
	case LanguageType::JAPANESE:
		return "ja";
	case LanguageType::KOREAN:
		return "ko";
	case LanguageType::NORWEGIAN:
		return "no";
	case LanguageType::POLISH:
		return "pl";
	case LanguageType::PORTUGUESE:
		return "pt";
	case LanguageType::PORTUGUESE_BRAZIL:
		return "pt-BR";
	case LanguageType::ROMANIAN:
		return "ro";
	case LanguageType::RUSSIAN:
		return "ru";
	case LanguageType::SPANISH:
		return "es";
	case LanguageType::SWEDISH:
		return "sv";
	case LanguageType::THAI:
		return "th";
	case LanguageType::TURKISH:
		return "tr";
	case LanguageType::UKRAINIAN:
		return "uk";
	case LanguageType::ENGLISH:
	default:
		return "en";
	}
}

float Localization::fontSizeH1(std::string fontResource)
{
	if (fontResource == Resources::Fonts_Marker_Felt)
	{
		return 48.0f;
	}
	else if (fontResource == Resources::Fonts_Monobit)
	{
		return 64.0f;
	}
	else if (fontResource == Resources::Fonts_Montserrat_Bold ||
		fontResource == Resources::Fonts_Montserrat_BoldItalic ||
		fontResource == Resources::Fonts_Montserrat_Italic ||
		fontResource == Resources::Fonts_Montserrat_Regular)
	{
		return 48.0f;
	}
	else if (fontResource == Resources::Fonts_UbuntuMono_Bold ||
		fontResource == Resources::Fonts_UbuntuMono_BoldItalic ||
		fontResource == Resources::Fonts_UbuntuMono_Italic ||
		fontResource == Resources::Fonts_UbuntuMono_Regular)
	{
		return 48.0f;
	}

	return 48.0f;
}

float Localization::fontSizeH2(std::string fontResource)
{
	if (fontResource == Resources::Fonts_Marker_Felt)
	{
		return 40.0f;
	}
	else if (fontResource == Resources::Fonts_Monobit)
	{
		return 56.0f;
	}
	else if (fontResource == Resources::Fonts_Montserrat_Bold ||
		fontResource == Resources::Fonts_Montserrat_BoldItalic ||
		fontResource == Resources::Fonts_Montserrat_Italic ||
		fontResource == Resources::Fonts_Montserrat_Regular)
	{
		return 40.0f;
	}
	else if (fontResource == Resources::Fonts_UbuntuMono_Bold ||
		fontResource == Resources::Fonts_UbuntuMono_BoldItalic ||
		fontResource == Resources::Fonts_UbuntuMono_Italic ||
		fontResource == Resources::Fonts_UbuntuMono_Regular)
	{
		return 40.0f;
	}

	return 40.0f;
}

float Localization::fontSizeH3(std::string fontResource)
{
	if (fontResource == Resources::Fonts_Marker_Felt)
	{
		return 36.0f;
	}
	else if (fontResource == Resources::Fonts_Monobit)
	{
		return 52.0f;
	}
	else if (fontResource == Resources::Fonts_Montserrat_Bold ||
		fontResource == Resources::Fonts_Montserrat_BoldItalic ||
		fontResource == Resources::Fonts_Montserrat_Italic ||
		fontResource == Resources::Fonts_Montserrat_Regular)
	{
		return 36.0f;
	}
	else if (fontResource == Resources::Fonts_UbuntuMono_Bold ||
		fontResource == Resources::Fonts_UbuntuMono_BoldItalic ||
		fontResource == Resources::Fonts_UbuntuMono_Italic ||
		fontResource == Resources::Fonts_UbuntuMono_Regular)
	{
		return 36.0f;
	}

	return 36.0f;
}

float Localization::fontSizeP(std::string fontResource)
{
	if (fontResource == Resources::Fonts_Marker_Felt)
	{
		return 24.0f;
	}
	else if (fontResource == Resources::Fonts_Monobit)
	{
		return 48.0f;
	}
	else if (fontResource == Resources::Fonts_Montserrat_Bold ||
		fontResource == Resources::Fonts_Montserrat_BoldItalic ||
		fontResource == Resources::Fonts_Montserrat_Italic ||
		fontResource == Resources::Fonts_Montserrat_Regular)
	{
		return 24.0f;
	}
	else if (fontResource == Resources::Fonts_UbuntuMono_Bold ||
		fontResource == Resources::Fonts_UbuntuMono_BoldItalic ||
		fontResource == Resources::Fonts_UbuntuMono_Italic ||
		fontResource == Resources::Fonts_UbuntuMono_Regular)
	{
		return 24.0f;
	}

	return 24.0f;
}
