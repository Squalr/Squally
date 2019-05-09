#include "Analytics.h"

#include "Engine/Analytics/TAnalytics.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Steam/Steam.h"
#include "Engine/Utils/SystemUtils.h"

using namespace cocos2d;

Analytics* Analytics::instance = nullptr;
const std::string Analytics::trackingCode = "UA-125390935-1";

void Analytics::registerGlobalNode()
{
	GlobalDirector::getInstance()->registerGlobalNode(Analytics::getInstance());
}

void Analytics::sendEvent(std::string category, std::string action, std::string label, int value)
{
	if (Analytics::areAnalyticsEnabled())
	{
		TAnalytics_Event(category.c_str(), action.c_str(), label.c_str(), value);
	}
}

void Analytics::sendEvent(std::string category, std::string action, std::string label)
{
	if (Analytics::areAnalyticsEnabled())
	{
		TAnalytics_Event(category.c_str(), action.c_str(), label.c_str());
	}
}

void Analytics::sendEvent(std::string category, std::string action)
{
	if (Analytics::areAnalyticsEnabled())
	{
		TAnalytics_Event(category.c_str(), action.c_str());
	}
}

void Analytics::shutDown()
{
	if (Analytics::areAnalyticsEnabled())
	{
		TAnalytics_Shutdown();
	}
}

Analytics* Analytics::getInstance()
{
	if (Analytics::instance == nullptr)
	{
		Analytics::instance = new Analytics();
	}

	return Analytics::instance;
}

Analytics::Analytics()
{
	if (Analytics::areAnalyticsEnabled())
	{
		TAnalytics_Init(Analytics::trackingCode.c_str(), SystemUtils::getUniqueSystemIdentifier().c_str());
	}
}

Analytics::~Analytics()
{
}

void Analytics::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Analytics::update(float dt)
{
	if (Analytics::areAnalyticsEnabled())
	{
		TAnalytics_Update();
	}
}

bool Analytics::areAnalyticsEnabled()
{
	// Analytics are currently disabled in Steam builds, and only on Itch.io (this is the price of being free for Itch)
	if (Steam::isSquallyItchBuild())
	{
		return true;
	}

	return false;
}
