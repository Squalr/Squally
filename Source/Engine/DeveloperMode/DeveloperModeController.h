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

private:
	typedef GlobalNode super;
	DeveloperModeController();
	virtual ~DeveloperModeController();

	void initializeListeners() override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	bool developerModeEnabled;

	static DeveloperModeController* instance;
};
