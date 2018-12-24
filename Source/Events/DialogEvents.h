#pragma once
#include <string>

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
