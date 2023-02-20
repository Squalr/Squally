#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class ArcaneProtectionGenericPreview : public HackablePreview
{
public:
	static ArcaneProtectionGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ArcaneProtectionGenericPreview();
	virtual ~ArcaneProtectionGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
