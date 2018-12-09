#pragma once
#include "cocos/2d/CCNode.h"

#include "Engine/Events/SceneEvents.h"

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
	virtual void initializePositions();
	virtual void initializeListeners();
	virtual void removeAllListeners();
	virtual void addEventListener(cocos2d::EventListener* listener);
	void addEventListenerIgnorePause(cocos2d::EventListener* listener);
};
