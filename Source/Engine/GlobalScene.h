#pragma once

#include "Engine/SmartScene.h"

class GlobalScene : public SmartScene
{
public:
	static GlobalScene* create();

	virtual void addGlobalEventListener(cocos2d::EventListener* listener);

private:
    typedef SmartScene super;
};
