#pragma once
#include <string>

class HelperEvents
{
public:
	static const std::string EventFindScrappy;
	static const std::string EventChangeHelper;

	struct ChangeHelperArgs
	{
		std::string helperName;

		ChangeHelperArgs(std::string helperName) : helperName(helperName)
		{
		}
	};

	static void TriggerFindScrappy();
	static void TriggerChangeHelper(ChangeHelperArgs args);
};
