#include "LocalizedString.h"

#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Localization/Localization.h"

using namespace cocos2d;

LocalizedString::LocalizedString()
{
	this->onLocaleChange = nullptr;
}

LocalizedString::~LocalizedString()
{
}

void LocalizedString::initializeListeners()
{
	super::initializeListeners();

	this->addGlobalEventListener(EventListenerCustom::create(LocalizationEvents::LocaleChangeEvent, [=](EventCustom* args)
	{
		if (this->onLocaleChange != nullptr)
		{
			this->onLocaleChange(this);
		}
	}));
}

std::string LocalizedString::getString()
{
	switch (Localization::getLanguage())
	{
		case LanguageType::ARABIC:
		{
			return this->getStringAr();
		}
		case LanguageType::BULGARIAN:
		{
			return this->getStringBg();
		}
		case LanguageType::CHINESE_SIMPLIFIED:
		{
			return this->getStringZhCn();
		}
		case LanguageType::CHINESE_TRADITIONAL:
		{
			return this->getStringZhTw();
		}
		case LanguageType::CZECH:
		{
			return this->getStringCs();
		}
		case LanguageType::DANISH:
		{
			return this->getStringDa();
		}
		case LanguageType::DUTCH:
		{
			return this->getStringNl();
		}
		case LanguageType::FINNISH:
		{
			return this->getStringFi();
		}
		case LanguageType::FRENCH:
		{
			return this->getStringFr();
		}
		case LanguageType::GERMAN:
		{
			return this->getStringDe();
		}
		case LanguageType::GREEK:
		{
			return this->getStringEl();
		}
		case LanguageType::HUNGARIAN:
		{
			return this->getStringHu();
		}
		case LanguageType::ITALIAN:
		{
			return this->getStringIt();
		}
		case LanguageType::JAPANESE:
		{
			return this->getStringJa();
		}
		case LanguageType::KOREAN:
		{
			return this->getStringKo();
		}
		case LanguageType::NORWEGIAN:
		{
			return this->getStringNo();
		}
		case LanguageType::POLISH:
		{
			return this->getStringPl();
		}
		case LanguageType::PORTUGUESE:
		{
			return this->getStringPt();
		}
		case LanguageType::PORTUGUESE_BRAZIL:
		{
			return this->getStringPtBr();
		}
		case LanguageType::ROMANIAN:
		{
			return this->getStringRo();
		}
		case LanguageType::RUSSIAN:
		{
			return this->getStringRu();
		}
		case LanguageType::SPANISH:
		{
			return this->getStringEs();
		}
		case LanguageType::SPANISH_LATIN_AMERICAN:
		{
			return this->getStringEs419();
		}
		case LanguageType::SWEDISH:
		{
			return this->getStringSv();
		}
		case LanguageType::THAI:
		{
			return this->getStringTh();
		}
		case LanguageType::TURKISH:
		{
			return this->getStringTr();
		}
		case LanguageType::UKRAINIAN:
		{
			return this->getStringUk();
		}
		case LanguageType::VIETNAMESE:
		{
			return this->getStringVn();
		}
		case LanguageType::ENGLISH:
		default:
		{
			return this->getStringEn();
		}
	}
}

void LocalizedString::setOnLocaleChangeCallback(std::function<void(LocalizedString* newString)> onLocaleChange)
{
	this->onLocaleChange = onLocaleChange;
}
