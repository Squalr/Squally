#include "LocalizedString.h"

#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Localization/Localization.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

LocalizedString::LocalizedString()
{
	this->overrideLanguage = LanguageType::NONE;
	this->onStringUpdate = nullptr;
	this->stringReplacementVariables = std::vector<LocalizedString*>();
	this->currentLanguage = Localization::getLanguage();
}

LocalizedString::~LocalizedString()
{
}

void LocalizedString::onEnter()
{
	// ZAC: Optimization to skip SmartNode onEnter(). LocalizedStrings do not need the events set up by the SmartNode base class.
	// Less stuff to dispose, this means significantly faster map destruction.
	Node::onEnter();

	if (this->currentLanguage != Localization::getLanguage())
	{
		this->onStringUpdate(this);
	}

	// This needs to be done here since we side-step SmartNode functions
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
	std::string localizedString = this->getStringByLanguage(this->overrideLanguage != LanguageType::NONE ? this->overrideLanguage : Localization::getLanguage());

	int index = 1;

	for (auto next : this->stringReplacementVariables)
	{
		if (next != nullptr)
		{
			localizedString = StrUtils::replaceAll(localizedString, "%s" + std::to_string(index++), next->getString());
		}
		else
		{
			localizedString = StrUtils::replaceAll(localizedString, "%s" + std::to_string(index++), "");
		}
	}

	return localizedString;
}

cocos2d::LanguageType LocalizedString::getOverrideLanguage()
{
	return this->overrideLanguage;
}

void LocalizedString::setOverrideLanguage(cocos2d::LanguageType overrideLanguage)
{
	this->overrideLanguage = overrideLanguage;
}

LocalizedString* LocalizedString::setStringReplacementVariables(LocalizedString* stringReplacementVariables)
{
	return this->setStringReplacementVariables(std::vector<LocalizedString*>({ stringReplacementVariables }));
}

LocalizedString* LocalizedString::setStringReplacementVariables(std::vector<LocalizedString*> stringReplacementVariables)
{
	// Release old replacement varaibles
	for (auto next : this->stringReplacementVariables)
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
			}
		}

		if (isReentry)
		{
			// Remove the child and retain it
			GameUtils::changeParent(next, nullptr, true, false);
		}
		else
		{
			// Remove the child and release it
			this->removeChild(next);
		}
	}

	this->stringReplacementVariables = stringReplacementVariables;

	// Retain new replacement variables
	for (auto next : this->stringReplacementVariables)
	{
		if (next == nullptr)
		{
			continue;
		}

		// Update this string if any of the replacement variables get updated
		next->setOnStringUpdateCallback([=](LocalizedString*)
		{
			if (this->onStringUpdate != nullptr)
			{
				this->onStringUpdate(this);
			}
		});
		
		this->addChild(next);
	}

	if (this->onStringUpdate != nullptr)
	{
		this->onStringUpdate(this);
	}

	return this;
}

void LocalizedString::setOnStringUpdateCallback(std::function<void(LocalizedString* newString)> onStringUpdate)
{
	this->onStringUpdate = onStringUpdate;
}

void LocalizedString::copyAttributesTo(LocalizedString* localizedString)
{
	localizedString->setOverrideLanguage(this->getOverrideLanguage());

	std::vector<LocalizedString*> stringReplacementVariables = std::vector<LocalizedString*>();

	for (auto next : this->stringReplacementVariables)
	{
		stringReplacementVariables.push_back(next == nullptr ? nullptr : next->clone());
	}

	localizedString->setStringReplacementVariables(stringReplacementVariables);
}
