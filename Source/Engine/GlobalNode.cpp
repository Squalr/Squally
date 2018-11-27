#include "GlobalNode.h"

void GlobalNode::pause()
{
	// Do nothing -- global nodes should not get paused
}

void GlobalNode::addEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	// Set a special flag to indicate the event listener is global -- prevents situations where the event listener might not otherwise fire
	listener->setIsGlobal(true);

	SmartNode::addEventListener(listener);
}
