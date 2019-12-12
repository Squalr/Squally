#pragma once

#include "Engine/Events/DeveloperModeEvents.h"
#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class Event;
}

class DeveloperModeController : public GlobalNode
{
public:
	static void registerGlobalNode();
	static DeveloperModeController* getInstance();

	bool isDeveloperModeEnabled();
	int getDebugLevel();

private:
	typedef GlobalNode super;
	DeveloperModeController();
	virtual ~DeveloperModeController();

	void initializeListeners() override;

	int currentDebugLevel;

	static DeveloperModeController* instance;
	static bool IsDeveloperBuild;
	static int MaxDebugLevel;
};
