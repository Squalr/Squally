#pragma once
#include "cocos2d.h"

#include "Resources.h"

using namespace cocos2d;

class SmartScene : public Scene
{
public:
	SmartScene();
	~SmartScene();

protected:
	virtual void onEnter() override;
	virtual void initializePositions();
	virtual void initializeListeners();
};

