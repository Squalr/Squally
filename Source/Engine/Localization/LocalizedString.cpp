#include "LocalizedString.h"

#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Localization/Localization.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

LocalizedString::LocalizedString()
{
	this->onStringUpdate = nullptr;
	this->stringReplacementVariables = std::vector<std::string>();
	this->currentLanguage = Localization::getLanguage();
}

LocalizedString::~LocalizedString()
{
}

void LocalizedString::onEnter()
{
	super::onEnter();

	if (this->currentLanguage != Localization::getLanguage())
	{
		this->onStringUpdate(this);
	}
}

void LocalizedString::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(LocalizationEvents::LocaleChangeEvent, [=](EventCustom* args)
	{
		if (this->onStringUpdate != nullptr)
		{
			this->onStringUpdate(this);
		}
	}));
}

std::string LocalizedString::getString()
{
	std::string localizedString;

	switch (Localization::getLanguage())
	{
		case LanguageType::ARABIC:
		{
			localizedString = this->getStringAr();
			break;
		}
		case LanguageType::BULGARIAN:
		{
			localizedString = this->getStringBg();
			break;
		}
		case LanguageType::CHINESE_SIMPLIFIED:
		{
			localizedString = this->getStringZhCn();
			break;
		}
		case LanguageType::CHINESE_TRADITIONAL:
		{
			localizedString = this->getStringZhTw();
			break;
		}
		case LanguageType::CZECH:
		{
			localizedString = this->getStringCs();
			break;
		}
		case LanguageType::DANISH:
		{
			localizedString = this->getStringDa();
			break;
		}
		case LanguageType::DUTCH:
		{
			localizedString = this->getStringNl();
			break;
		}
		case LanguageType::FINNISH:
		{
			localizedString = this->getStringFi();
			break;
		}
		case LanguageType::FRENCH:
		{
			localizedString = this->getStringFr();
			break;
		}
		case LanguageType::GERMAN:
		{
			localizedString = this->getStringDe();
			break;
		}
		case LanguageType::GREEK:
		{
			localizedString = this->getStringEl();
			break;
		}
		case LanguageType::HUNGARIAN:
		{
			localizedString = this->getStringHu();
			break;
		}
		case LanguageType::ITALIAN:
		{
			localizedString = this->getStringIt();
			break;
		}
		case LanguageType::JAPANESE:
		{
			localizedString = this->getStringJa();
			break;
		}
		case LanguageType::KOREAN:
		{
			localizedString = this->getStringKo();
			break;
		}
		case LanguageType::NORWEGIAN:
		{
			localizedString = this->getStringNo();
			break;
		}
		case LanguageType::POLISH:
		{
			localizedString = this->getStringPl();
			break;
		}
		case LanguageType::PORTUGUESE:
		{
			localizedString = this->getStringPt();
			break;
		}
		case LanguageType::PORTUGUESE_BRAZIL:
		{
			localizedString = this->getStringPtBr();
			break;
		}
		case LanguageType::ROMANIAN:
		{
			localizedString = this->getStringRo();
			break;
		}
		case LanguageType::RUSSIAN:
		{
			localizedString = this->getStringRu();
			break;
		}
		case LanguageType::SPANISH:
		{
			localizedString = this->getStringEs();
			break;
		}
		case LanguageType::SPANISH_LATIN_AMERICAN:
		{
			localizedString = this->getStringEs419();
			break;
		}
		case LanguageType::SWEDISH:
		{
			localizedString = this->getStringSv();
			break;
		}
		case LanguageType::THAI:
		{
			localizedString = this->getStringTh();
			break;
		}
		case LanguageType::TURKISH:
		{
			localizedString = this->getStringTr();
			break;
		}
		case LanguageType::UKRAINIAN:
		{
			localizedString = this->getStringUk();
			break;
		}
		case LanguageType::VIETNAMESE:
		{
			localizedString = this->getStringVi();
			break;
		}
		case LanguageType::ENGLISH:
		default:
		{
			localizedString = this->getStringEn();
			break;
		}
	}

	for (auto it = this->stringReplacementVariables.begin(); it != this->stringReplacementVariables.end(); it++)
	{
		localizedString = StrUtils::replaceFirstOccurence(localizedString, "%s", *it);
	}

	return localizedString;
}

void LocalizedString::setStringReplacementVariables(std::vector<std::string> stringReplacementVariables)
{
	this->stringReplacementVariables = stringReplacementVariables;

	if (this->onStringUpdate != nullptr)
	{
		this->onStringUpdate(this);
	}
}

void LocalizedString::setOnStringUpdateCallback(std::function<void(LocalizedString* newString)> onLocaleChange)
{
	this->onStringUpdate = onLocaleChange;
}
