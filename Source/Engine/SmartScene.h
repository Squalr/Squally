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

	SmartScene();
	virtual ~SmartScene();

	void setFadeSpeed(float newFadeSpeed);
	float getFadeSpeed();

protected:
	void pause() override;
	void onEnter() override;
	void onExit() override;
	virtual void onDeveloperModeEnable();
	virtual void onDeveloperModeDisable();
	virtual void onHackerModeEnable(int eq);
	virtual void onHackerModeDisable();
	bool isDeveloperModeEnabled();
	virtual void initializePositions();
	virtual void initializeListeners();
	virtual void removeAllListeners();
	virtual void removeNonGlobalListeners();
	virtual void addEventListener(cocos2d::EventListener* listener);
	virtual void removeEventListener(cocos2d::EventListener* listener);
	void addEventListenerIgnorePause(cocos2d::EventListener* listener);
	void whenKeyPressed(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyPressedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyPressedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyReleased(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyReleasedIgnorePause(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);
	void whenKeyReleasedHackerMode(std::set<cocos2d::EventKeyboard::KeyCode> keyCodes, std::function<void(InputEvents::InputArgs*)> callback, bool requireVisible = true);

	bool hackermodeEnabled;
	Hud* layerColorHud;
	cocos2d::LayerColor* layerColor;
	cocos2d::FiniteTimeAction* fadeAction;
	float fadeSpeed;

	static const float defaultFadeSpeed;
private:
	typedef cocos2d::Scene super;
};

