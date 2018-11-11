#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Engine/Utils/HackUtils.h"
#include "Resources.h"

using namespace cocos2d;
using namespace cocos_experimental;

class HackerMode : public SmartNode
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
