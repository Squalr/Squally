#pragma once
#include "cocos/2d/CCNode.h"

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

	void resume() override;

protected:
	void onEnter() override;
	void onReenter() override; // Called on parent change
	virtual void onDeveloperModeEnable();
	virtual void onDeveloperModeDisable();
	bool isDeveloperModeEnabled();
	virtual void initializePositions();
	virtual void initializeListeners();
	virtual void removeAllListeners();
	virtual void addEventListener(cocos2d::EventListener* listener);
	virtual void removeEventListener(cocos2d::EventListener* listener);
	void addEventListenerIgnorePause(cocos2d::EventListener* listener);
private:
	typedef cocos2d::Node super;
};
