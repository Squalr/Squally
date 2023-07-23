#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class DefensiveStanceGenericPreview : public HackablePreview
{
public:
	static DefensiveStanceGenericPreview* create();

	HackablePreview* clone() override;

protected:
	DefensiveStanceGenericPreview();
	virtual ~DefensiveStanceGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
