#include "WarpGateExactScanTutorial.h"

int WarpGateExactScanTutorial::warpGatePower = 0;
int WarpGateExactScanTutorial::warpGatePowerMax = 70100;

WarpGateExactScanTutorial* WarpGateExactScanTutorial::create(ValueMap* initProperties)
{
	WarpGateExactScanTutorial* instance = new WarpGateExactScanTutorial(initProperties);

	instance->autorelease();

	return instance;
}

WarpGateExactScanTutorial::WarpGateExactScanTutorial(ValueMap* initProperties) : WarpGate(initProperties)
{
	this->valueLabel = Label::create(std::to_string(WarpGateExactScanTutorial::warpGatePower), Localization::getMainFont(), 24.0f);

	this->valueLabel->setPosition(0, 256.0f);
	this->valueLabel->enableOutline(Color4B::BLACK, 2.0f);

	this->addChild(this->valueLabel);
}

WarpGateExactScanTutorial::~WarpGateExactScanTutorial()
{
}

void WarpGateExactScanTutorial::onEnter()
{
	WarpGate::onEnter();

	CallFunc* incPower = CallFunc::create([=]
	{
		this->incrementPower();
	});

	incPower->retain();

	this->runAction(RepeatForever::create(
		Sequence::create(
			incPower,
			DelayTime::create(1.0f),
			nullptr)
		)
	);

	this->scheduleUpdate();
}

void WarpGateExactScanTutorial::incrementPower()
{
	ASM(push eax);
	ASM(mov eax dword WarpGateExactScanTutorial::warpGatePower);

	void* assemblyAddressStart = nullptr;
	void* assemblyAddressEnd = nullptr;

	HACKABLE_CODE_BEGIN(assemblyAddressStart, startIncrementPower)
	ASM(inc eax);
	ASM(nop);
	ASM(nop);
	ASM(nop);
	ASM(nop);
	HACKABLE_CODE_BEGIN(assemblyAddressEnd, endIncrementPower)

	ASM(mov WarpGateExactScanTutorial::warpGatePower dword eax);
	ASM(pop eax);

	static bool init = false;

	if (!init)
	{
		init = true;

		int byteCount = (int)((unsigned long)assemblyAddressEnd - (unsigned long)assemblyAddressStart);
		// HackableCode* hackablePower = HackableCode::create("Recharge Power", assemblyAddressStart, byteCount, Resources::Menus_HackerModeMenu_Icons_Heart, Resources::Menus_HackerModeMenu_Icons_Heart);
		// this->registerCode(hackablePower);
	}
}

void WarpGateExactScanTutorial::update(float dt)
{
	// Update text if values have changed
	if (~previousValue != WarpGateExactScanTutorial::warpGatePower || ~previousValueMax != WarpGateExactScanTutorial::warpGatePowerMax)
	{
		// Constrain value
		WarpGateExactScanTutorial::warpGatePower = std::min(WarpGateExactScanTutorial::warpGatePower, WarpGateExactScanTutorial::warpGatePowerMax);

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
