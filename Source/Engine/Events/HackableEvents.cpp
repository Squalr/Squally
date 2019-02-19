#include "HackableEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string HackableEvents::HackerModeEnable = "EVENT_HACKERMODE_ENABLE";
const std::string HackableEvents::HackerModeDisable = "EVENT_HACKERMODE_DISABLE";
const std::string HackableEvents::HackableObjectOpenEvent = "EVENT_OPEN_HACKABLE_OBJECT";
const std::string HackableEvents::HackableObjectCloseEvent = "EVENT_CLOSE_HACKABLE_OBJECT";
const std::string HackableEvents::HackableAttributeEditEvent = "EVENT_EDIT_HACKABLE_OBJECT";
const std::string HackableEvents::HackableAttributeEditDoneEvent = "EVENT_EDIT_HACKABLE_OBJECT_DONE";
const std::string HackableEvents::HackableObjectRegisterEvent = "EVENT_REGISTER_HACKABLE_OBJECT";
const std::string HackableEvents::HackAppliedEvent = "EVENT_HACK_APPLIED";

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

void HackableEvents::TriggerOpenHackable(HackableObjectOpenArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HackableEvents::HackableObjectOpenEvent,
		&args
	);
}

void HackableEvents::TriggerCloseHackable()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HackableEvents::HackableObjectCloseEvent
	);
}

void HackableEvents::TriggerEditHackableAttribute(HackableObjectEditArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HackableEvents::HackableAttributeEditEvent,
		&args
	);
}

void HackableEvents::TriggerEditHackableAttributeDone()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HackableEvents::HackableAttributeEditDoneEvent
	);
}

void HackableEvents::TriggerRegisterHackable(HackableObjectRegisterArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HackableEvents::HackableObjectRegisterEvent,
		&args
	);
}

void HackableEvents::TriggerOnHackApplied(HackAppliedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		HackableEvents::HackAppliedEvent,
		&args
	);
}
