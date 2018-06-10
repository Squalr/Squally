#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Objects/Hackables/HackableObject.h"

using namespace cocos2d;

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
		Vec2 sourceLocation;
		 
		HackableObjectEditArgs(HackableObject* hackableObject, Vec2 sourceLocation) : hackableObject(hackableObject), sourceLocation(sourceLocation)
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
