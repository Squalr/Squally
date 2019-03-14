#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class ParticleSystem;
}

class LocalizedLabel;

class WindSetSpeedPreview : public HackablePreview
{
public:
	static WindSetSpeedPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	WindSetSpeedPreview();
	virtual ~WindSetSpeedPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::ParticleSystem* windParticles;
	LocalizedLabel* eaxPositive;
	LocalizedLabel* eaxNegative;
	LocalizedLabel* ebxPositive;
	LocalizedLabel* ebxNegative;
};
