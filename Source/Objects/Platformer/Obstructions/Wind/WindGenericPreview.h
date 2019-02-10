#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class ParticleSystem;
}

class WindGenericPreview : public HackablePreview
{
public:
	static WindGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	WindGenericPreview();
	virtual ~WindGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::ParticleSystem* windParticles;
};
