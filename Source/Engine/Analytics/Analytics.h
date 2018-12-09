#pragma once
#include "Engine/GlobalNode.h"

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
	virtual ~Analytics();

	void onEnter() override;
	void update(float dt) override;

	static Analytics* instance;
	static const std::string trackingCode;
};
