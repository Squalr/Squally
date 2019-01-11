#pragma once
#include <string>

#include "cocos/math/Vec2.h"

class HackableAttribute;
class HackableObject;

class HackableEvents
{
public:
	struct HackableObjectOpenArgs
	{
		HackableObject* hackableObject;

		HackableObjectOpenArgs(HackableObject* hackableObject) :hackableObject(hackableObject) { }
	};

	struct HackableObjectEditArgs
	{
		HackableAttribute* hackableAttribute;

		HackableObjectEditArgs(HackableAttribute* hackableAttribute) :hackableAttribute(hackableAttribute) { }
	};

	struct HackableObjectRegisterArgs
	{
		HackableObject* hackableObject;

		HackableObjectRegisterArgs(HackableObject* hackableObject) : hackableObject(hackableObject)
		{
		}
	};

	static void TriggerHackerModeEnable();
	static void TriggerHackerModeDisable();
	static void TriggerOpenHackable(HackableObjectOpenArgs args);
	static void TriggerCloseHackable();
	static void TriggerEditHackableAttribute(HackableObjectEditArgs args);
	static void TriggerEditHackableAttributeDone();
	static void TriggerRegisterHackable(HackableObjectRegisterArgs args);

	static const std::string HackerModeEnable;
	static const std::string HackerModeDisable;
	static const std::string HackableObjectOpenEvent;
	static const std::string HackableObjectCloseEvent;
	static const std::string HackableAttributeEditEvent;
	static const std::string HackableAttributeEditDoneEvent;
	static const std::string HackableObjectRegisterEvent;
};
