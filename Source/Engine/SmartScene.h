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

	virtual void resume() override;

protected:
	virtual void onEnter() override;
	virtual void initializePositions();
	virtual void initializeListeners();
	virtual void removeAllListeners();
	void addEventListener(cocos2d::EventListener* listener);
	void addEventListenerIgnorePause(cocos2d::EventListener* listener);
};

