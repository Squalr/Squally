#pragma once
#include <string>

#include "cocos/math/Vec2.h"

class Clippy;
class HackableAttribute;
class HackableObject;

class HackableEvents
{
public:
	static const std::string EventHackerModeEnable;
	static const std::string EventHackerModeDisable;
	static const std::string EventAllowHackerMode;
	static const std::string EventDisallowHackerMode;
	static const std::string EventHackableObjectOpen;
	static const std::string EventHackableObjectClose;
	static const std::string EventHackableAttributeEdit;
	static const std::string EventHackableAttributeEditDone;
	static const std::string EventHackableObjectRegister;
	static const std::string EventHackApplied;
	static const std::string EventOpenLexiconPage;
	static const std::string EventCloseLeftLexiconPage;
	static const std::string EventCloseRightLexiconPage;

	struct HackableObjectOpenArgs
	{
		HackableObject* hackableObject;

		HackableObjectOpenArgs(HackableObject* hackableObject) : hackableObject(hackableObject) { }
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

	struct HackAppliedArgs
	{
		HackableAttribute* activeAttribute;

		HackAppliedArgs(HackableAttribute* activeAttribute) : activeAttribute(activeAttribute)
		{
		}
	};

	struct OpenLexiconPageArgs
	{
		std::string pageIdentifier;

		OpenLexiconPageArgs(std::string pageIdentifier) : pageIdentifier(pageIdentifier)
		{
		}
	};

	static void TriggerHackerModeEnable();
	static void TriggerHackerModeDisable();
	static void TriggerAllowHackerMode();
	static void TriggerDisallowHackerMode();
	static void TriggerOpenHackable(HackableObjectOpenArgs args);
	static void TriggerCloseHackable();
	static void TriggerEditHackableAttribute(HackableObjectEditArgs args);
	static void TriggerEditHackableAttributeDone();
	static void TriggerRegisterHackable(HackableObjectRegisterArgs args);
	static void TriggerOnHackApplied(HackAppliedArgs args);
	static void TriggerOpenLexiconPage(OpenLexiconPageArgs args);
	static void TriggerCloseLeftLexiconPage();
	static void TriggerCloseRightLexiconPage();
};
