#include "GlobalScene.h"

#include "cocos/base/CCEventListener.h"

using namespace cocos2d;

void GlobalScene::addGlobalEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	listener->setIsGlobal(true);

	super::addEventListener(listener);
}
