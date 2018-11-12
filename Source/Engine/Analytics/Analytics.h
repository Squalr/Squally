#pragma once
#include "cocos2d.h"

#include "Engine/Analytics/TAnalytics.h"
#include "Engine/GlobalDirector.h"
#include "Engine/GlobalNode.h"
#include "Engine/Utils/SystemUtils.h"
#include "Resources.h"

using namespace cocos2d;

class Analytics : public GlobalNode
{
public:
	static void registerGlobalNode();
	static void shutDown();
	static void sendEvent(std::string category, std::string action, std::string label, int value);
	static void sendEvent(std::string category, std::string action, std::string label);
	static void sendEvent(std::string category, std::string action);

private:
	static Analytics * getInstance();
	Analytics();
	~Analytics();

	void onEnter() override;
	void update(float dt) override;

	static Analytics* instance;
	static const std::string trackingCode;
};
