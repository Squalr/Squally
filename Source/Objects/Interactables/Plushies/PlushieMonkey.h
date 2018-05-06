#pragma once
#include "cocos2d.h"
#include "Plushie.h"

using namespace cocos2d;

class PlushieMonkey : public Plushie
{
public:
	static PlushieMonkey* create();

protected:
	PlushieMonkey();
	~PlushieMonkey();

	void update(float) override;
	void onEnter() override;
	void registerHackables() override;

private:
	HackableData * puzzleData;

	void incrementPower();

	Label* valueLabel;

	int previousValue;
	int previousValueMax;

	static int warpGatePower;
	static int warpGatePowerMax;
};
