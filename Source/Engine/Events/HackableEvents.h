#pragma once
#include <string>

class HackableBase;
class HackableObject;

struct HackableObjectOpenArgs
{
	HackableObject* hackableObject;
	int hackFlags;

	HackableObjectOpenArgs(HackableObject* hackableObject, int hackFlags) : hackableObject(hackableObject), hackFlags(hackFlags) { }
};

struct HackableObjectEditArgs
{
	HackableObject* hackableObject;
	HackableBase* hackableAttribute;

	HackableObjectEditArgs(HackableObject* hackableObject, HackableBase* hackableAttribute) : hackableObject(hackableObject), hackableAttribute(hackableAttribute) { }
};

struct HackAppliedArgs
{
	HackableBase* activeAttribute;

	HackAppliedArgs(HackableBase* activeAttribute) : activeAttribute(activeAttribute)
	{
	}
};

struct HackToggleArgs
{
	HackToggleArgs()
	{
	}
};

struct HackFlagsChangedArgs
{
	int hackFlags;

	HackFlagsChangedArgs(int hackFlags) : hackFlags(hackFlags) { }
};

struct HackerModeQueryArgs
{
	bool hackerModeAllowed;

	HackerModeQueryArgs() : hackerModeAllowed(false)
	{
	}
};

struct HackableBaseQueryArgs
{
	std::string hackableIdentifier;
	int count;

	HackableBaseQueryArgs(std::string hackableIdentifier) : hackableIdentifier(hackableIdentifier), count(0)
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

class HackableEvents
{
public:
	static const std::string EventForceUseHackerMode;
	static const std::string EventHackerModeToggle;
	static const std::string EventHackerModeEnable;
	static const std::string EventHackerModeDisable;
	static const std::string EventAllowHackerMode;
	static const std::string EventDisallowHackerMode;
	static const std::string EventQueryHackerModeAllowed;
	static const std::string EventHackableObjectOpen;
	static const std::string EventHackableObjectClose;
	static const std::string EventHackableBaseEdit;
	static const std::string EventHackableBaseEditDone;
	static const std::string EventHackApplied;
	static const std::string EventHackFlagsChanged;
	static const std::string EventPauseHackTimers;
	static const std::string EventResumeHackTimers;
	static const std::string EventOpenLexiconPage;
	static const std::string EventCloseLeftLexiconPage;
	static const std::string EventCloseRightLexiconPage;

	static void TriggerForceUseHackerMode();
	static void TriggerHackerModeToggle(HackToggleArgs args);
	static void TriggerHackerModeEnable(HackToggleArgs args);
	static void TriggerHackerModeDisable();
	static void TriggerAllowHackerMode();
	static void TriggerDisallowHackerMode();
	static void TriggerQueryHackerModeAllowed(HackerModeQueryArgs* args);
	static void TriggerOpenHackable(HackableObjectOpenArgs args);
	static void TriggerCloseHackable();
	static void TriggerEditHackableBase(HackableObjectEditArgs args);
	static void TriggerEditHackableBaseDone();
	static void TriggerOnHackApplied(HackAppliedArgs args);
	static void TriggerHackFlagsChanged(HackFlagsChangedArgs args);
	static void TriggerPauseHackTimers();
	static void TriggerResumeHackTimers();
	static void TriggerOpenLexiconPage(OpenLexiconPageArgs args);
	static void TriggerCloseLeftLexiconPage();
	static void TriggerCloseRightLexiconPage();
};
