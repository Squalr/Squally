#include "HackableEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string HackableEvents::HackableObjectEditEvent = "hackable_object_edit_event";
const std::string HackableEvents::HackableObjectRegisterEvent = "hackable_object_register_event";

void HackableEvents::editHackable(HackableObjectEditArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HackableEvents::HackableObjectEditEvent,
		&args
	);
}

void HackableEvents::registerHackable(HackableObjectRegisterArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HackableEvents::HackableObjectRegisterEvent,
		&args
	);
}
