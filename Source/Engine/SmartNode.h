#pragma once
#include "cocos2d.h"

#include "Engine/Events/SceneEvents.h"

using namespace cocos2d;

class SmartNode : public Node
{
public:
	SmartNode();
	~SmartNode();

	virtual void resume() override;

protected:
	virtual void onEnter() override;
	virtual void onReenter() override; // Called on parent change
	virtual void initializePositions();
	virtual void initializeListeners();
	virtual void removeAllListeners();
	virtual void addEventListener(EventListener* listener);
	void addEventListenerIgnorePause(EventListener* listener);
};
