#include "GlobalNode.h"

#include "cocos/base/CCEventListener.h"

using namespace cocos2d;

void GlobalNode::pause()
{
	// Do nothing -- global nodes should not get paused
}

void GlobalNode::addGlobalEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	listener->setIsGlobal(true);

	super::addEventListener(listener);
}
