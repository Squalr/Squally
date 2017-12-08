#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Game : public cocos2d::Scene
{
public:
	virtual bool init();

	static Scene* createScene();

	// A selector callback
	void menuCloseCallback(Ref* pSender);

	// Implement the "static create()" method manually
	CREATE_FUNC(Game);
};
