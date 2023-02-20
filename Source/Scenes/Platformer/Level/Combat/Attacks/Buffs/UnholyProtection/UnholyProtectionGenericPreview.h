#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class UnholyProtectionGenericPreview : public HackablePreview
{
public:
	static UnholyProtectionGenericPreview* create();

	HackablePreview* clone() override;

protected:
	UnholyProtectionGenericPreview();
	virtual ~UnholyProtectionGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
