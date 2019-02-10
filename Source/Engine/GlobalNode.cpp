#include "GlobalNode.h"

#include "cocos/base/CCEventListener.h"

using namespace cocos2d;

GlobalNode* GlobalNode::create()
{
	GlobalNode* instance = new GlobalNode();

	instance->autorelease();

	return instance;
}

GlobalNode::GlobalNode()
{
}

GlobalNode::~GlobalNode()
{
}

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
