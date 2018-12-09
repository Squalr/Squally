#pragma once
#include <string>

#include "cocos/math/Vec2.h"

// Forward declarations
class HackableObject;

class HackableEvents
{
public:
	static const std::string HackableObjectEditEvent;
	static const std::string HackableObjectRegisterEvent;

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

	static void editHackable(HackableObjectEditArgs args);
	static void registerHackable(HackableObjectRegisterArgs args);
};
