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

protected:
	WindGenericPreview();
	virtual ~WindGenericPreview();
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::ParticleSystem* windParticles;
};
