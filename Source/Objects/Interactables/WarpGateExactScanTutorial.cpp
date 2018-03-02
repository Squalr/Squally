#include "WarpGateExactScanTutorial.h"

int WarpGateExactScanTutorial::warpGatePower = 69420666;
int WarpGateExactScanTutorial::warpGatePowerMax = 70100200;

WarpGateExactScanTutorial* WarpGateExactScanTutorial::create()
{
	WarpGateExactScanTutorial* warpGate = new WarpGateExactScanTutorial();

	warpGate->autorelease();

	return warpGate;
}

WarpGateExactScanTutorial::WarpGateExactScanTutorial() : WarpGate::WarpGate()
{
	this->valueLabel = Label::create("Temp", Resources::Fonts_Montserrat_Medium, 24);

	this->valueLabel->setPosition(0, 256.0f);
	this->valueLabel->enableOutline(Color4B::BLACK, 2.0f);

	this->addChild(this->valueLabel);

	this->scheduleUpdate();
}

WarpGateExactScanTutorial::~WarpGateExactScanTutorial()
{
}

void WarpGateExactScanTutorial::update(float dt)
{
	// Update text if values have changed
	if (~previousValue != WarpGateExactScanTutorial::warpGatePower || ~previousValueMax != WarpGateExactScanTutorial::warpGatePowerMax)
	{
		// Constrain value
		WarpGateExactScanTutorial::warpGatePower = min(WarpGateExactScanTutorial::warpGatePower, WarpGateExactScanTutorial::warpGatePowerMax);

		// Update text
		this->valueLabel->setString(std::to_string(WarpGateExactScanTutorial::warpGatePower) + " / " + std::to_string(WarpGateExactScanTutorial::warpGatePowerMax));

		// Set color
		if (WarpGateExactScanTutorial::warpGatePower < WarpGateExactScanTutorial::warpGatePowerMax)
		{
			this->valueLabel->setColor(Color3B::RED);
			this->close();
		}
		else
		{
			this->valueLabel->setColor(Color3B::GREEN);
			this->open();
		}

		// Store the previous value as a bit inverse (so that the previous values do not show up in scan results)
		previousValue = ~WarpGateExactScanTutorial::warpGatePower;
		previousValueMax = ~WarpGateExactScanTutorial::warpGatePowerMax;
	}
}
