#pragma once
#include "cocos/2d/CCScene.h"

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
	SmartScene();
	virtual ~SmartScene();

	void setFadeSpeed(float newFadeSpeed);
	float getFadeSpeed();
	virtual void resume() override;

protected:
	virtual void pause() override;
	virtual void onEnter() override;
	virtual void onDeveloperModeEnable();
	virtual void onDeveloperModeDisable();
	bool isDeveloperModeEnabled();
	virtual void initializePositions();
	virtual void initializeListeners();
	virtual void removeAllListeners();
	virtual void addEventListener(cocos2d::EventListener* listener);
	void addGlobalEventListener(cocos2d::EventListener* listener);
	void addEventListenerIgnorePause(cocos2d::EventListener* listener);

	Hud* layerColorHud;
	cocos2d::LayerColor* layerColor;
	cocos2d::FiniteTimeAction* fadeAction;
	float fadeSpeed;

	static const float defaultFadeSpeed;
private:
	typedef cocos2d::Scene super;
};

