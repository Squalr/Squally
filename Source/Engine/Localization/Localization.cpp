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
	std::string localizedStringsJson = FileUtils::getInstance()->getStringFromFile(Resources::LocalizedStrings.c_str());

	this->localizationMap = new Document();
	this->localizationMap->Parse<0>(localizedStringsJson.c_str());
}

Localization::~Localization()
{
	delete(this->localizationMap);
}

std::string Localization::resolveDialog(std::string dialogFileEN)
{
	Localization* manager = Localization::getInstance();

	// This list is a joke, TODO update engine to support useful languages https://www.andovar.com/what-languages/

	switch (Application::getInstance()->getCurrentLanguage())
	{
	case LanguageType::ARABIC:
		break;
	case LanguageType::BELARUSIAN:
		break;
	case LanguageType::BULGARIAN:
		break;
	case LanguageType::CHINESE:
		break;
	case LanguageType::DUTCH:
		break;
	case LanguageType::FRENCH:
		break;
	case LanguageType::GERMAN:
		break;
	case LanguageType::HUNGARIAN:
		break;
	case LanguageType::ITALIAN:
		break;
	case LanguageType::JAPANESE:
		break;
	case LanguageType::KOREAN:
		break;
	case LanguageType::NORWEGIAN:
		break;
	case LanguageType::ROMANIAN:
		break;
	case LanguageType::RUSSIAN:
		break;
	case LanguageType::SPANISH:
		break;
	case LanguageType::TURKISH:
		break;
	case LanguageType::UKRAINIAN:
		break;
	case LanguageType::ENGLISH:
	default:
		break;
	}

	return dialogFileEN;
}

std::string Localization::resolveString(std::string resourceKey)
{
	Localization* manager = Localization::getInstance();

	if (manager->localizationMap->HasMember(resourceKey.c_str()))
	{
		auto node = (*manager->localizationMap)[resourceKey.c_str()].GetObjectW();

		switch (Application::getInstance()->getCurrentLanguage())
		{
		case LanguageType::ARABIC:
			break;
		case LanguageType::BELARUSIAN:
			break;
		case LanguageType::BULGARIAN:
			break;
		case LanguageType::CHINESE:
			break;
		case LanguageType::DUTCH:
			break;
		case LanguageType::FRENCH:
			break;
		case LanguageType::GERMAN:
			break;
		case LanguageType::HUNGARIAN:
			break;
		case LanguageType::ITALIAN:
			break;
		case LanguageType::JAPANESE:
			break;
		case LanguageType::KOREAN:
			break;
		case LanguageType::NORWEGIAN:
			break;
		case LanguageType::ROMANIAN:
			break;
		case LanguageType::RUSSIAN:
			break;
		case LanguageType::SPANISH:
			break;
		case LanguageType::TURKISH:
			break;
		case LanguageType::UKRAINIAN:
			break;
		case LanguageType::ENGLISH:
		default:
			return node["EN"].GetString();
			break;
		}
	}

	CCLOG(("Localization resource key not found: " + resourceKey).c_str());
	return resourceKey;
}
