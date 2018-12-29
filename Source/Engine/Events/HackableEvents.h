#pragma once
#include <string>

#include "cocos/math/Vec2.h"

class HackableObject;

class HackableEvents
{
public:
	struct HackableObjectEditArgs
	{
		HackableObject* hackableObject;
		cocos2d::Vec2 sourceLocation;

		HackableObjectEditArgs(HackableObject* hackableObject, cocos2d::Vec2 sourceLocation) :
			hackableObject(hackableObject), sourceLocation(sourceLocation)
		{
		}
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
	static void TriggerEditHackable(HackableObjectEditArgs args);
	static void TriggerRegisterHackable(HackableObjectRegisterArgs args);

	static const std::string HackerModeEnable;
	static const std::string HackerModeDisable;
	static const std::string HackableObjectEditEvent;
	static const std::string HackableObjectRegisterEvent;
};
