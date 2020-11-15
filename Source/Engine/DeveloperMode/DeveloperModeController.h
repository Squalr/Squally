#pragma once

#include "Engine/GlobalNode.h"

class DeveloperModeController : public GlobalNode
{
public:
	static void registerGlobalNode();

	static bool isDeveloperModeEnabled();
	static int getDebugLevel();
	
	static volatile bool IsDeveloperBuild;
	static volatile bool ShowFPSInfo;

protected:
	DeveloperModeController();
	virtual ~DeveloperModeController();

	static DeveloperModeController* getInstance();

	void onEnter() override;
	void initializeListeners() override;

private:
	typedef GlobalNode super;

	static int CurrentDebugLevel;

	static DeveloperModeController* instance;
	static int MaxDebugLevel;
};
