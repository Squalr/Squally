#include "GlobalNode.h"

#include "cocos/base/CCEventListener.h"

using namespace cocos2d;

void GlobalNode::pause()
{
	// Do nothing -- global nodes should not get paused
}

void GlobalNode::addEventListener(EventListener* listener)
{
	// Force events to be added as global events for global nodes
	SmartNode::addGlobalEventListener(listener);
}
