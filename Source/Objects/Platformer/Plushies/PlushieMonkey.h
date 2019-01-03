#pragma once

#include "Objects/Platformer/Plushies/Plushie.h"
#include "Engine/Localization/ConstantString.h"

class ConstantString;
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
	typedef HackableObject super;
	HackableData* puzzleData;

	void decreaseLockTimer();

	ConstantString* valueString;
	LocalizedLabel* valueLabel;

	int previousValue;
	int previousValueMax;

	static int lockCountDown;
};
