#include "Analytics.h"

#include "Engine/Analytics/TAnalytics.h"
#include "Engine/GlobalDirector.h"
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
	TAnalytics_Event(category.c_str(), action.c_str(), label.c_str(), value);
}

void Analytics::sendEvent(std::string category, std::string action, std::string label)
{
	TAnalytics_Event(category.c_str(), action.c_str(), label.c_str());
}

void Analytics::sendEvent(std::string category, std::string action)
{
	TAnalytics_Event(category.c_str(), action.c_str());
}

void Analytics::shutDown()
{
	TAnalytics_Shutdown();
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
	TAnalytics_Init(Analytics::trackingCode.c_str(), SystemUtils::getUniqueSystemIdentifier().c_str());
}

Analytics::~Analytics()
{
}

void Analytics::onEnter()
{
	GlobalNode::onEnter();

	this->scheduleUpdate();
}

void Analytics::update(float dt)
{
	TAnalytics_Update();
}
