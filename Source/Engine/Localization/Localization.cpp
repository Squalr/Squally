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
	std::string localizedStringsJson = FileUtils::getInstance()->getStringFromFile(StringResources::Menus.c_str());

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
		auto node = (*localization->localizationMap)[resourceKey.c_str()].GetObject();
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
	// TEMP!
	return "en";
	
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
			return FontResources::Pixel_Zpix;
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
		case LanguageType::SWEDISH:
		case LanguageType::THAI:
		case LanguageType::TURKISH:
		case LanguageType::UKRAINIAN:
			// TODO
			return FontResources::Pixel_Zpix;
	}
}

std::string Localization::getMainFont()
{
	switch (Application::getInstance()->getCurrentLanguage())
	{
		default:
		case LanguageType::ENGLISH:
			return FontResources::Montserrat_Medium;
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
		case LanguageType::SWEDISH:
		case LanguageType::THAI:
		case LanguageType::TURKISH:
		case LanguageType::UKRAINIAN:
			// TODO
			return FontResources::Montserrat_Medium;
	}
}

std::string Localization::getCodingFont()
{
	switch (Application::getInstance()->getCurrentLanguage())
	{
		default:
		case LanguageType::ENGLISH:
			return FontResources::UbuntuMono_Bold;
		case LanguageType::CHINESE_SIMPLIFIED:
		case LanguageType::CHINESE_TRADITIONAL:
		case LanguageType::JAPANESE:
		case LanguageType::KOREAN:
			return FontResources::Ubuntu_WenQuanYiMicroHeiMono_02;
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
		case LanguageType::SWEDISH:
		case LanguageType::THAI:
		case LanguageType::TURKISH:
		case LanguageType::UKRAINIAN:
			// TODO
			return FontResources::UbuntuMono_Bold;
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
