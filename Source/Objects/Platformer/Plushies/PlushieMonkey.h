#pragma once

#include "Objects/Platformer/Plushies/Plushie.h"

class LocalizedLabel;

class PlushieMonkey : public Plushie
{
public:
	static PlushieMonkey* create(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyPlushieMonkey;

protected:
	PlushieMonkey(cocos2d::ValueMap* initProperties);
	~PlushieMonkey();

	void update(float) override;
	void onEnter() override;
	void registerHackables() override;

private:
	HackableData* puzzleData;

	void decreaseLockTimer();

	LocalizedLabel* valueLabel;

	int previousValue;
	int previousValueMax;

	static int lockCountDown;
};
