#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/WarpGate.h"

using namespace cocos2d;

class WarpGateExactScanTutorial : public WarpGate
{
public:
	static WarpGateExactScanTutorial* create(ValueMap* initProperties);

	static const std::string MapKeyWarpGateExactScanTutorial;

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
