#pragma once
#include <set>

#include "cocos/2d/CCNode.h"
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/Events/InputEvents.h"

namespace cocos2d
{
	class EventListener;
}

class SmartNode : public cocos2d::Node
{
public:
	static SmartNode* create();

	virtual void addEventListener(cocos2d::EventListener* listener);
	virtual void removeEventListener(cocos2d::EventListener* listener);
	virtual void removeEventListenerByTag(std::string tag);
	void addEventListenerIgnorePause(cocos2d::EventListener* listener);
	void addGlobalEventListener(cocos2d::EventListener* listener);
	cocos2d::EventListener* whenKeyPressed(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	cocos2d::EventListener* whenKeyPressedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	cocos2d::EventListener* whenKeyPressedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	cocos2d::EventListener* whenKeyReleased(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	cocos2d::EventListener* whenKeyReleasedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	cocos2d::EventListener* whenKeyReleasedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void onDispose(std::function<void()> task);

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
	void defer(std::function<void()> task);
	void scheduleEvery(std::function<void()> task, float seconds);

	bool hackermodeEnabled;
	
private:
	typedef cocos2d::Node super;

	static unsigned long long TaskId;

	bool optimizationHasGlobalListener;
	bool optimizationHasListener;
	bool hasInitializedListeners;

	std::vector<std::function<void()>> disposeCallbacks;
};
