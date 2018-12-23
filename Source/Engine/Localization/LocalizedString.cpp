#include "LocalizedString.h"

#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/LocalizationEvents.h"

using namespace cocos2d;

std::string LocalizedString::getString()
{
	return this->localizedString;
}

LocalizedString::LocalizedString(std::function<void(std::string newString)> onLocaleChange)
{
	this->onLocaleChange = onLocaleChange;
}

LocalizedString::~LocalizedString()
{
}

void LocalizedString::initializeListeners()
{
	SmartNode::initializeListeners();

	this->addEventListener(EventListenerCustom::create(LocalizationEvents::LocaleChangeEvent, [=](EventCustom* args)
	{
		this->onLocaleChange("");
	}));
}
