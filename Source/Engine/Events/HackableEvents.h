#pragma once
#include <string>

#include "cocos/math/Vec2.h"

class Clippy;
class HackableAttribute;
class HackableObject;

class HackableEvents
{
public:
	static const std::string EventForceHackerModeEnable;
	static const std::string EventHackerModeToggle;
	static const std::string EventHackerModeEnable;
	static const std::string EventHackerModeDisable;
	static const std::string EventAllowHackerMode;
	static const std::string EventDisallowHackerMode;
	static const std::string EventQueryHackerModeAllowed;
	static const std::string EventHackableObjectOpen;
	static const std::string EventHackableObjectClose;
	static const std::string EventHackableAttributeEdit;
	static const std::string EventHackableAttributeEditDone;
	static const std::string EventHackApplied;
	static const std::string EventOpenLexiconPage;
	static const std::string EventCloseLeftLexiconPage;
	static const std::string EventCloseRightLexiconPage;

	struct HackableObjectOpenArgs
	{
		HackableObject* hackableObject;
		int hackFlags;

		HackableObjectOpenArgs(HackableObject* hackableObject, int hackFlags) : hackableObject(hackableObject), hackFlags(hackFlags) { }
	};

	struct HackableObjectEditArgs
	{
		HackableAttribute* hackableAttribute;

		HackableObjectEditArgs(HackableAttribute* hackableAttribute) :hackableAttribute(hackableAttribute) { }
	};

	struct HackAppliedArgs
	{
		HackableAttribute* activeAttribute;

		HackAppliedArgs(HackableAttribute* activeAttribute) : activeAttribute(activeAttribute)
		{
		}
	};

	struct HackToggleArgs
	{
		int hackFlags;

		HackToggleArgs(int hackFlags) : hackFlags(hackFlags)
		{
		}
	};

	struct HackerModeQueryArgs
	{
		bool hackerModeAllowed;

		HackerModeQueryArgs() : hackerModeAllowed(false)
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

	static void TriggerForceHackerModeEnable();
	static void TriggerHackerModeToggle(HackToggleArgs args);
	static void TriggerHackerModeEnable(HackToggleArgs args);
	static void TriggerHackerModeDisable();
	static void TriggerAllowHackerMode();
	static void TriggerDisallowHackerMode();
	static void TriggerQueryHackerModeAllowed(HackerModeQueryArgs* args);
	static void TriggerOpenHackable(HackableObjectOpenArgs args);
	static void TriggerCloseHackable();
	static void TriggerEditHackableAttribute(HackableObjectEditArgs args);
	static void TriggerEditHackableAttributeDone();
	static void TriggerOnHackApplied(HackAppliedArgs args);
	static void TriggerOpenLexiconPage(OpenLexiconPageArgs args);
	static void TriggerCloseLeftLexiconPage();
	static void TriggerCloseRightLexiconPage();
};
