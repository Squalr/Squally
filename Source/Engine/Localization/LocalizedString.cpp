#include "LocalizedString.h"

#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/LocalizationEvents.h"

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
	SmartNode::initializeListeners();

	this->addGlobalEventListener(EventListenerCustom::create(LocalizationEvents::LocaleChangeEvent, [=](EventCustom* args)
	{
		if (this->onLocaleChange != nullptr)
		{
			this->onLocaleChange(this->getString());
		}
	}));
}

std::string LocalizedString::getString()
{
	return this->localizedString;
}

void LocalizedString::setOnLocaleChangeCallback(std::function<void(std::string newString)> onLocaleChange)
{
	this->onLocaleChange = onLocaleChange;
}
