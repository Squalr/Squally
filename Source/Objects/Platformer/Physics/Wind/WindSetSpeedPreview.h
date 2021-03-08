#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class LocalizedLabel;
class SmartParticles;

class WindSetSpeedPreview : public HackablePreview
{
public:
	static WindSetSpeedPreview* create();

	HackablePreview* clone() override;

protected:
	WindSetSpeedPreview();
	virtual ~WindSetSpeedPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartParticles* windParticles;
	LocalizedLabel* eaxPositive;
	LocalizedLabel* eaxNegative;
	LocalizedLabel* ebxPositive;
	LocalizedLabel* ebxNegative;
};
