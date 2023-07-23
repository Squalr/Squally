#include "LocalizedString.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListener.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Localization/Localization.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

LocalizedString::LocalizedString()
{
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
		this->doStringUpdate();
	}
}

void LocalizedString::initializeListeners()
{
	super::initializeListeners();

	this->addGlobalEventListener(EventListenerCustom::create(LocalizationEvents::LocaleChangeEvent, [=](EventCustom* args)
	{
		this->doStringUpdate();
	}));
}

std::string LocalizedString::getString()
{
	std::string localizedString = this->getStringByLanguage(this->overrideLanguage != LanguageType::NONE ? this->overrideLanguage : Localization::getLanguage());

	// Reverse iterate to ensure that templates with more digits are processed first.
	// For example, %s10 is processed before %s1. The reverse order would result in %s10 being treated as "{%s1}" + "0", which is wrong.
	for (int index = int(this->stringReplacementVariables.size()); index >= 1; index--)
	{
		LocalizedString* next = stringReplacementVariables[index - 1];

		if (next != nullptr)
		{
			localizedString = StrUtils::replaceAll(localizedString, "%s" + std::to_string(index), next->getString());
		}
		else
		{
			localizedString = StrUtils::replaceAll(localizedString, "%s" + std::to_string(index), "");
		}
	}

	return localizedString;
}

cocos2d::LanguageType LocalizedString::getOverrideLanguage()
{
	return this->overrideLanguage;
}

LocalizedString* LocalizedString::setOverrideLanguage(cocos2d::LanguageType overrideLanguage)
{
	this->overrideLanguage = overrideLanguage;

	return this;
}

LocalizedString* LocalizedString::setStringReplacementVariables(LocalizedString* stringReplacementVariables)
{
	return this->setStringReplacementVariables(std::vector<LocalizedString*>({ stringReplacementVariables }));
}

std::vector<LocalizedString*> LocalizedString::getStringReplacementVariables()
{
	return this->stringReplacementVariables;
}

LocalizedString* LocalizedString::setStringReplacementVariables(std::vector<LocalizedString*> stringReplacementVariables)
{
	// Release old replacement varaibles
	for (LocalizedString* next : this->stringReplacementVariables)
	{
		if (next == nullptr)
		{
			continue;
		}

		bool isReentry = false;

		for (auto compareIt = stringReplacementVariables.begin(); compareIt != stringReplacementVariables.end(); compareIt++)
		{
			if (next == *compareIt)
			{
				isReentry = true;
				break;
			}
		}

		if (isReentry)
		{
			// Remove the child and retain it
			GameUtils::changeParent(next, nullptr, false);
		}
		else
		{
			// Remove the child and release it
			this->removeChild(next);
		}
	}

	this->stringReplacementVariables = stringReplacementVariables;

	// Retain new replacement variables
	for (LocalizedString* next : this->stringReplacementVariables)
	{
		if (next == nullptr)
		{
			continue;
		}

		// Update this string if any of the replacement variables get updated
		next->setOnStringUpdateCallback([=]()
		{
			this->doStringUpdate();
		});
		
		this->addChild(next);
	}

	this->doStringUpdate();

	return this;
}

void LocalizedString::setOnStringUpdateCallback(std::function<void()> onStringUpdate)
{
	this->onStringUpdate = onStringUpdate;
}

void LocalizedString::copyAttributesTo(LocalizedString* localizedString)
{
	localizedString->setOverrideLanguage(this->getOverrideLanguage());

	std::vector<LocalizedString*> stringReplacementVariables = std::vector<LocalizedString*>();

	for (LocalizedString* next : this->stringReplacementVariables)
	{
		stringReplacementVariables.push_back(next == nullptr ? nullptr : next->clone());
	}

	localizedString->setStringReplacementVariables(stringReplacementVariables);
}

void LocalizedString::doStringUpdate()
{
	this->currentLanguage = Localization::getLanguage();
	
	if (this->onStringUpdate != nullptr)
	{
		this->onStringUpdate();
	}
}
