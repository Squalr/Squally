#pragma once
#include "cocos/2d/CCNode.h"

namespace cocos2d
{
	class EventListener;
}

class SmartNode : public cocos2d::Node
{
public:
	SmartNode();
	virtual ~SmartNode();

	virtual void resume() override;

protected:
	virtual void onEnter() override;
	virtual void onReenter() override; // Called on parent change
	virtual void onDeveloperModeEnable();
	virtual void onDeveloperModeDisable();
	bool isDeveloperModeEnabled();
	virtual void initializePositions();
	virtual void initializeListeners();
	virtual void removeAllListeners();
	virtual void addEventListener(cocos2d::EventListener* listener);
	void addGlobalEventListener(cocos2d::EventListener* listener);
	void addEventListenerIgnorePause(cocos2d::EventListener* listener);
};
