#include "GlobalScene.h"

#include "cocos/base/CCEventListener.h"

using namespace cocos2d;

GlobalScene* GlobalScene::create()
{
	GlobalScene* instance = new GlobalScene();

	instance->autorelease();

	return instance;
}

GlobalScene::GlobalScene()
{
}

GlobalScene::~GlobalScene()
{
}

void GlobalScene::addGlobalEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	listener->setIsGlobal(true);

	super::addEventListener(listener);
}
