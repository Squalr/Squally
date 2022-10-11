#include "Analytics.h"

#include "Engine/Analytics/TAnalytics.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Steam/Steam.h"
#include "Engine/Utils/SystemUtils.h"

using namespace cocos2d;

Analytics* Analytics::Instance = nullptr;
const std::string Analytics::TrackingCode = "UA-125390935-1";

void Analytics::RegisterGlobalNode()
{
	GlobalDirector::getInstance()->RegisterGlobalNode(Analytics::getInstance());
}

Analytics* Analytics::getInstance()
{
	if (Analytics::Instance == nullptr)
	{
		Analytics::Instance = new Analytics();
	}

	return Analytics::Instance;
}

Analytics::Analytics()
{
	if (Analytics::areAnalyticsEnabled())
	{
		TAnalytics_Init(Analytics::TrackingCode.c_str(), SystemUtils::GetUniqueSystemIdentifier().c_str());
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

bool Analytics::areAnalyticsEnabled()
{
	// Analytics are currently disabled in Steam builds
	if (!Steam::IsSquallySteamBuild())
	{
		return true;
	}

	return false;
}
