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
	void addEventListenerIgnorePause(cocos2d::EventListener* listener);
	void whenKeyPressed(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyPressedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyPressedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyReleased(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyReleasedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyReleasedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);

protected:
	SmartNode();
	~SmartNode();
	void onEnter() override;

	// IMPORTANT: This method may not get called if the object is being disposed (new scene) as an optimization.
	// Instead, put critical exit code in a BeforeSceneChange event listener.	
	void onExit() override;
	void onReenter() override; // Called on parent change
	virtual void onDeveloperModeEnable();
	virtual void onDeveloperModeDisable();
	virtual void onHackerModeEnable(int eq);
	virtual void onHackerModeDisable();
	bool isDeveloperModeEnabled();
	virtual void initializePositions();
	virtual void initializeListeners();
	virtual void removeAllListeners();
	virtual void removeNonGlobalListeners();

	bool hackermodeEnabled;
	
private:
	typedef cocos2d::Node super;

	bool optimizationHasGlobalListener;
	bool optimizationHasListener;
};
