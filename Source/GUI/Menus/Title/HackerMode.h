#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/Utils.h"

using namespace cocos2d;
using namespace experimental;

class HackerMode : public Node
{
public:
	static HackerMode * GetInstance();
	std::string GetHackerModeAddressHex();

	const std::string HackerModeEnabledEvent = "hacker_mode_enabled_event";

private:
	HackerMode();
	~HackerMode();

	void update(float) override;

	static int hackerMode;
	static HackerMode* hackerModeInstance;
};
