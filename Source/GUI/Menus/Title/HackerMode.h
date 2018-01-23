#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/HackUtils.h"

using namespace cocos2d;
using namespace experimental;

class HackerMode : public Node
{
public:
	static HackerMode * getInstance();
	std::string getHackerModeAddressHex();

	static const std::string HackerModeEnabledEvent;

private:
	HackerMode();
	~HackerMode();

	void update(float) override;

	static int hackerMode;
	static HackerMode* hackerModeInstance;
};
