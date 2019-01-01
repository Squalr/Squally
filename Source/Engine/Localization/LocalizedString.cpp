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
		}
		case LanguageType::BULGARIAN:
		{
			localizedString = this->getStringBg();
		}
		case LanguageType::CHINESE_SIMPLIFIED:
		{
			localizedString = this->getStringZhCn();
		}
		case LanguageType::CHINESE_TRADITIONAL:
		{
			localizedString = this->getStringZhTw();
		}
		case LanguageType::CZECH:
		{
			localizedString = this->getStringCs();
		}
		case LanguageType::DANISH:
		{
			localizedString = this->getStringDa();
		}
		case LanguageType::DUTCH:
		{
			localizedString = this->getStringNl();
		}
		case LanguageType::FINNISH:
		{
			localizedString = this->getStringFi();
		}
		case LanguageType::FRENCH:
		{
			localizedString = this->getStringFr();
		}
		case LanguageType::GERMAN:
		{
			localizedString = this->getStringDe();
		}
		case LanguageType::GREEK:
		{
			localizedString = this->getStringEl();
		}
		case LanguageType::HUNGARIAN:
		{
			localizedString = this->getStringHu();
		}
		case LanguageType::ITALIAN:
		{
			localizedString = this->getStringIt();
		}
		case LanguageType::JAPANESE:
		{
			localizedString = this->getStringJa();
		}
		case LanguageType::KOREAN:
		{
			localizedString = this->getStringKo();
		}
		case LanguageType::NORWEGIAN:
		{
			localizedString = this->getStringNo();
		}
		case LanguageType::POLISH:
		{
			localizedString = this->getStringPl();
		}
		case LanguageType::PORTUGUESE:
		{
			localizedString = this->getStringPt();
		}
		case LanguageType::PORTUGUESE_BRAZIL:
		{
			localizedString = this->getStringPtBr();
		}
		case LanguageType::ROMANIAN:
		{
			localizedString = this->getStringRo();
		}
		case LanguageType::RUSSIAN:
		{
			localizedString = this->getStringRu();
		}
		case LanguageType::SPANISH:
		{
			localizedString = this->getStringEs();
		}
		case LanguageType::SPANISH_LATIN_AMERICAN:
		{
			localizedString = this->getStringEs419();
		}
		case LanguageType::SWEDISH:
		{
			localizedString = this->getStringSv();
		}
		case LanguageType::THAI:
		{
			localizedString = this->getStringTh();
		}
		case LanguageType::TURKISH:
		{
			localizedString = this->getStringTr();
		}
		case LanguageType::UKRAINIAN:
		{
			localizedString = this->getStringUk();
		}
		case LanguageType::VIETNAMESE:
		{
			localizedString = this->getStringVi();
		}
		case LanguageType::ENGLISH:
		default:
		{
			localizedString = this->getStringEn();
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
