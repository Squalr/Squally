#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartParticles;

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

	SmartParticles* windParticles;
};
