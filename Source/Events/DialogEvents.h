#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class DialogEvents
{
public:
	static const std::string DialogOpenEvent;

	struct DialogOpenArgs
	{
		std::string dialogResource;

		DialogOpenArgs(std::string dialogResource) : dialogResource(dialogResource)
		{
		}
	};

	static void TriggerDialog(DialogOpenArgs args);
};
