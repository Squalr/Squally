#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class LocalizedLabel;
class SmartParticles;

class BlizzardSetSpeedPreview : public HackablePreview
{
public:
	static BlizzardSetSpeedPreview* create();

	HackablePreview* clone() override;

protected:
	BlizzardSetSpeedPreview();
	virtual ~BlizzardSetSpeedPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartParticles* blizzardParticles = nullptr;
	LocalizedLabel* eaxPositive = nullptr;
	LocalizedLabel* eaxNegative = nullptr;
	LocalizedLabel* ebxPositive = nullptr;
	LocalizedLabel* ebxNegative = nullptr;
};
