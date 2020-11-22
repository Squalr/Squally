#pragma once
#include <set>

#include "cocos/2d/CCNode.h"
#include "cocos/base/CCInputEvents.h"

namespace cocos2d
{
	class EventListenerCustom;
	class EventListener;
}

struct KeyboardEventArgs;
struct MouseEventArgs;

class SmartNode : public cocos2d::Node
{
public:
	static SmartNode* create();

	virtual void addEventListener(cocos2d::EventListenerCustom* listener);
	void addEventListenerIgnorePause(cocos2d::EventListenerCustom* listener);
	void addGlobalEventListener(cocos2d::EventListenerCustom* listener);
	virtual void removeEventListener(cocos2d::EventListenerCustom* listener);
	cocos2d::EventListenerCustom* whenKeyPressed(std::set<cocos2d::InputEvents::KeyCode> keyCodes, std::function<void(cocos2d::InputEvents::KeyboardEventArgs*)> callback, bool requireVisible = true);
	cocos2d::EventListenerCustom* whenKeyPressedIgnorePause(std::set<cocos2d::InputEvents::KeyCode> keyCodes, std::function<void(cocos2d::InputEvents::KeyboardEventArgs*)> callback, bool requireVisible = true);
	cocos2d::EventListenerCustom* whenKeyPressedHackerMode(std::set<cocos2d::InputEvents::KeyCode> keyCodes, std::function<void(cocos2d::InputEvents::KeyboardEventArgs*)> callback, bool requireVisible = true);
	cocos2d::EventListenerCustom* whenKeyReleased(std::set<cocos2d::InputEvents::KeyCode> keyCodes, std::function<void(cocos2d::InputEvents::KeyboardEventArgs*)> callback, bool requireVisible = true);
	cocos2d::EventListenerCustom* whenKeyReleasedIgnorePause(std::set<cocos2d::InputEvents::KeyCode> keyCodes, std::function<void(cocos2d::InputEvents::KeyboardEventArgs*)> callback, bool requireVisible = true);
	cocos2d::EventListenerCustom* whenKeyReleasedHackerMode(std::set<cocos2d::InputEvents::KeyCode> keyCodes, std::function<void(cocos2d::InputEvents::KeyboardEventArgs*)> callback, bool requireVisible = true);
	cocos2d::EventListenerCustom* whenScrollUp(std::function<void(cocos2d::InputEvents::MouseEventArgs*)> callback, bool requireVisible = true);
	cocos2d::EventListenerCustom* whenScrollDown(std::function<void(cocos2d::InputEvents::MouseEventArgs*)> callback, bool requireVisible = true);

protected:
	SmartNode();
	virtual ~SmartNode();
	void onEnter() override;

	// IMPORTANT: This method may not get called if the object is being disposed (new scene) as an optimization.
	// Instead, put critical exit code in a BeforeSceneChange event listener, or in the destructor.	
	void onExit() override;
	void onReenter() override; // Called on parent change
	virtual void onDeveloperModeEnable(int debugLevel);
	virtual void onDeveloperModeDisable();
	virtual void onHackerModeEnable();
	virtual void onHackerModeDisable();
	bool isDeveloperModeEnabled();
	virtual void initializePositions();
	virtual void initializeListeners();
	virtual void removeAllListeners();
	virtual void removeNonGlobalListeners();
	void defer(std::function<void()> task, int ticks = 1);
	void scheduleEvery(std::function<void()> task, float seconds);

	bool hackermodeEnabled;
	bool disableHackerModeEvents;
	
private:
	typedef cocos2d::Node super;

	std::set<cocos2d::EventListenerCustom*> listeners;
	std::set<cocos2d::EventListenerCustom*> listenersIgnorePause;
	std::set<cocos2d::EventListenerCustom*> listenersGlobal;

	static unsigned long long TaskId;
};
