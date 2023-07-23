#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class ScaldingBladeGenericPreview : public HackablePreview
{
public:
	static ScaldingBladeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ScaldingBladeGenericPreview();
	virtual ~ScaldingBladeGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
