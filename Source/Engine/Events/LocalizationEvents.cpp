#include "LocalizationEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string LocalizationEvents::BeforeLocaleChangeEvent = "EVENT_BEFORE_LOCALE_CHANGE";
const std::string LocalizationEvents::LocaleChangeEvent = "EVENT_LOCALE_CHANGE";
const std::string LocalizationEvents::TranslationBeginEdit = "EVENT_BEGIN_EDIT";

void LocalizationEvents::TriggerLocaleChange(LocaleChangeArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		LocalizationEvents::BeforeLocaleChangeEvent,
		&args
	);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		LocalizationEvents::LocaleChangeEvent,
		&args
	);
}

void LocalizationEvents::TriggerTranslationBeginEdit(TranslationBeginEditArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		LocalizationEvents::TranslationBeginEdit,
		&args
	);
}
