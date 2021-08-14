#pragma once
#include "Engine/GlobalNode.h"

class Analytics : public GlobalNode
{
public:
	static void RegisterGlobalNode();
	static void shutDown();
	static void sendEvent(std::string category, std::string action, std::string label, int value);
	static void sendEvent(std::string category, std::string action, std::string label);
	static void sendEvent(std::string category, std::string action);

protected:
	Analytics();
	virtual ~Analytics();

	void onEnter() override;
	void update(float dt) override;

private:
	typedef GlobalNode super;
	static Analytics * getInstance();

	static bool areAnalyticsEnabled();

	static Analytics* instance;
	static const std::string trackingCode;
};
