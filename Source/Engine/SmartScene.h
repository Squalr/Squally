#pragma once
#include <set>

#include "cocos/2d/CCScene.h"
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/Events/InputEvents.h"

namespace cocos2d
{
	class EventListener;
	class LayerColor;
	class FiniteTimeAction;
}

class Hud;

class SmartScene : public cocos2d::Scene
{
public:
	static SmartScene* create();

	void setFadeSpeed(float newFadeSpeed);
	float getFadeSpeed();
	virtual void addEventListener(cocos2d::EventListener* listener);
	virtual void removeEventListener(cocos2d::EventListener* listener);
	void addEventListenerIgnorePause(cocos2d::EventListener* listener);
	void addGlobalEventListener(cocos2d::EventListener* listener);
	void whenKeyPressed(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyPressedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyPressedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyReleased(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyReleasedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyReleasedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void onDispose(std::function<void()> task);

protected:
	SmartScene();
	virtual ~SmartScene();
	void pause() override;
	void onEnter() override;
	void onExit() override;
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

	bool hackermodeEnabled;
	Hud* layerColorHud;
	cocos2d::LayerColor* layerColor;
	cocos2d::FiniteTimeAction* fadeAction;
	float fadeSpeed;

	static const float defaultFadeSpeed;

private:
	typedef cocos2d::Scene super;

	std::vector<std::function<void()>> disposeCallbacks;

	static unsigned long long TaskId;
};

