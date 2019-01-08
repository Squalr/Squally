#include "HackableEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string HackableEvents::HackerModeEnable = "EVENT_HACKERMODE_ENABLE";
const std::string HackableEvents::HackerModeDisable = "EVENT_HACKERMODE_DISABLE";
const std::string HackableEvents::HackableObjectEditEvent = "EVENT_EDIT_HACKABLE_OBJECT";
const std::string HackableEvents::HackableObjectEditDoneEvent = "EVENT_EDIT_HACKABLE_OBJECT_DONE";
const std::string HackableEvents::HackableObjectRegisterEvent = "EVENT_REGISTER_HACKABLE_OBJECT";

void HackableEvents::TriggerHackerModeEnable()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HackableEvents::HackerModeEnable
	);
}

void HackableEvents::TriggerHackerModeDisable()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HackableEvents::HackerModeDisable
	);
}

void HackableEvents::TriggerEditHackable(HackableObjectEditArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HackableEvents::HackableObjectEditEvent,
		&args
	);
}

void HackableEvents::TriggerEditHackableDone()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HackableEvents::HackableObjectEditDoneEvent
	);
}

void HackableEvents::TriggerRegisterHackable(HackableObjectRegisterArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HackableEvents::HackableObjectRegisterEvent,
		&args
	);
}
