#pragma once
#include <string>
#include <vector>

#include "cocos/math/CCGeometry.h"

class HelperEvents
{
public:
	static const std::string EventFindFlyBot;
	static const std::string EventChangeHelper;

	struct ChangeHelperArgs
	{
		std::string helperName;

		ChangeHelperArgs(std::string helperName) : helperName(helperName)
		{
		}
	};

	static void TriggerFindFlyBot();
	static void TriggerChangeHelper(ChangeHelperArgs args);
};
