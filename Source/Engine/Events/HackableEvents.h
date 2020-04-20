#pragma once
#include <string>

#include "cocos/math/Vec2.h"

class Clippy;
class HackableBase;
class HackableObject;

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
	static const std::string EventQueryAttributeCountPrefix;
	static const std::string EventHackApplied;
	static const std::string EventHackRestoreStatePrefix;
	static const std::string EventHackFlagsChanged;
	static const std::string EventPauseHackTimers;
	static const std::string EventResumeHackTimers;
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
		HackableBase* hackableAttribute;

		HackableObjectEditArgs(HackableBase* hackableAttribute) :hackableAttribute(hackableAttribute) { }
	};

	struct HackAppliedArgs
	{
		HackableBase* activeAttribute;

		HackAppliedArgs(HackableBase* activeAttribute) : activeAttribute(activeAttribute)
		{
		}
	};

	struct HackRestoreStateArgs
	{
		std::string hackableObjectIdentifier;

		HackRestoreStateArgs(std::string hackableObjectIdentifier) : hackableObjectIdentifier(hackableObjectIdentifier), handled(false)
		{
		}

		void handle()
		{
			this->handled = true;
		}

		bool isHandled()
		{
			return this->handled;
		}

		private:
			bool handled;
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
	static void TriggerQueryAttributeCount(HackableBaseQueryArgs* args);
	static void TriggerOnHackApplied(HackAppliedArgs args);
	static void TriggerHackRestoreState(HackRestoreStateArgs args);
	static void TriggerHackFlagsChanged(HackFlagsChangedArgs args);
	static void TriggerPauseHackTimers();
	static void TriggerResumeHackTimers();
	static void TriggerOpenLexiconPage(OpenLexiconPageArgs args);
	static void TriggerCloseLeftLexiconPage();
	static void TriggerCloseRightLexiconPage();
};
