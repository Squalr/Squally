#pragma once
#include "cocos/2d/CCScene.h"

namespace cocos2d
{
	class EventListener;
}

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
	virtual void initializePositions();
	virtual void initializeListeners();
	virtual void removeAllListeners();
	void addEventListener(cocos2d::EventListener* listener);
	void addEventListenerIgnorePause(cocos2d::EventListener* listener);

	LayerColor* layerColor;
	FiniteTimeAction* fadeAction;
	float fadeSpeed;

	static const float defaultFadeSpeed;
};

