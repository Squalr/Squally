#pragma once
#include "cocos2d.h"
#include "Objects/Collision/CollisionObject.h"
#include "Objects/Interactables/WarpGate.h"
#include "GUI/Components/OutlineLabel.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class WarpGateExactScanTutorial : public WarpGate
{
public:
	static WarpGateExactScanTutorial* create();

private:
	WarpGateExactScanTutorial();
	~WarpGateExactScanTutorial();

	void update(float) override;

	OutlineLabel* valueLabel;

	int previousValue;
	int previousValueMax;

	static int warpGatePower;
	static int warpGatePowerMax;
};
