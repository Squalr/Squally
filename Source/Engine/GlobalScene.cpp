#include "GlobalScene.h"

void GlobalScene::addGlobalEventListener(EventListener* listener)
{
	if (listener == nullptr)
	{
		return;
	}

	// Set a special flag to indicate the event listener is global -- prevents situations where the event listener might not otherwise fire
	listener->setIsGlobal(true);

	SmartScene::addEventListener(listener);
}
