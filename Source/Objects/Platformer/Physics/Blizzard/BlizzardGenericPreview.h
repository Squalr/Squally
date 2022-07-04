#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartParticles;

class BlizzardGenericPreview : public HackablePreview
{
public:
	static BlizzardGenericPreview* create();

	HackablePreview* clone() override;

protected:
	BlizzardGenericPreview();
	virtual ~BlizzardGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartParticles* blizzardParticles = nullptr;
};
