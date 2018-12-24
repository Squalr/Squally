#include "LocalizationEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string LocalizationEvents::LocaleChangeEvent = "EVENT_LOCALE_CHANGE";

void LocalizationEvents::TriggerLocaleChange(LocaleChangeArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		LocalizationEvents::LocaleChangeEvent,
		&args
	);
}
