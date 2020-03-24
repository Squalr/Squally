#include "GlobalHud.h"

#include "cocos/base/CCEventListener.h"

using namespace cocos2d;

GlobalHud* GlobalHud::create()
{
	GlobalHud* instance = new GlobalHud();

	instance->autorelease();

	return instance;
}

GlobalHud::GlobalHud()
{
}

GlobalHud::~GlobalHud()
{
}

void GlobalHud::pause()
{
	// Do nothing -- global nodes should not get paused
}
