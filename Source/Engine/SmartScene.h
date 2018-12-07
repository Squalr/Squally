#pragma once
#include "cocos2d.h"

#include "Engine/Events/SceneEvents.h"

using namespace cocos2d;

class SmartScene : public Scene
{
public:
	SmartScene();
	~SmartScene();

	void setFadeSpeed(float newFadeSpeed);
	float getFadeSpeed();
	virtual void resume() override;

protected:
	virtual void pause() override;
	virtual void onEnter() override;
	virtual void initializePositions();
	virtual void initializeListeners();
	virtual void removeAllListeners();
	void addEventListener(EventListener* listener);
	void addEventListenerIgnorePause(EventListener* listener);

	LayerColor* layerColor;
	FiniteTimeAction* fadeAction;
	float fadeSpeed;

	static const float defaultFadeSpeed;
};

