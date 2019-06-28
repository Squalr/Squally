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

	SmartNode();
	virtual ~SmartNode();

protected:
	void onEnter() override;
	void onExit() override;
	void onReenter() override; // Called on parent change
	virtual void onDeveloperModeEnable();
	virtual void onDeveloperModeDisable();
	virtual void onHackerModeEnable();
	virtual void onHackerModeDisable();
	bool isDeveloperModeEnabled();
	virtual void initializePositions();
	virtual void initializeListeners();
	virtual void removeAllListeners();
	virtual void removeNonGlobalListeners();
	virtual void addEventListener(cocos2d::EventListener* listener);
	virtual void removeEventListener(cocos2d::EventListener* listener);
	void addEventListenerIgnorePause(cocos2d::EventListener* listener);
	void whenKeyPressed(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback);
	void whenKeyPressedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback);
	void whenKeyPressedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback);
	void whenKeyReleased(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback);
	void whenKeyReleasedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback);
	void whenKeyReleasedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback);

	bool hackermodeEnabled;
	
private:
	typedef cocos2d::Node super;
};
