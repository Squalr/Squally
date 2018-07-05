#pragma once
#include "cocos2d.h"

#include "Engine/Utils/GameUtils.h"
#include "Objects/Interactables/WarpGate.h"

using namespace cocos2d;

class WarpGateExactScanTutorial : public WarpGate
{
public:
	static WarpGateExactScanTutorial* create(ValueMap* initProperties);

private:
	WarpGateExactScanTutorial(ValueMap* initProperties);
	~WarpGateExactScanTutorial();

	void onEnter() override;
	void update(float) override;
	void incrementPower();

	Label* valueLabel;

	int previousValue;
	int previousValueMax;

	static int warpGatePower;
	static int warpGatePowerMax;
};
