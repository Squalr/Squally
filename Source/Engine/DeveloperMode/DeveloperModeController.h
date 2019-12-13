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
	
	static bool IsDeveloperBuild;

protected:
	DeveloperModeController();
	virtual ~DeveloperModeController();

	void onEnter() override;
	void initializeListeners() override;

private:
	typedef GlobalNode super;

	int currentDebugLevel;

	static DeveloperModeController* instance;
	static int MaxDebugLevel;
};
