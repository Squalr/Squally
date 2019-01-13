#include "GlobalHud.h"

#include "cocos/base/CCEventListener.h"

using namespace cocos2d;

GlobalHud* GlobalHud::create()
{
	GlobalHud* instance = new GlobalHud();

	instance->autorelease();

	return instance;
}

void GlobalHud::pause()
{
	// Do nothing -- global nodes should not get paused
}

void GlobalHud::addGlobalEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	listener->setIsGlobal(true);

	super::addEventListener(listener);
}
