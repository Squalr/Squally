#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class LocalizedLabel;
class SmartAnimationSequenceNode;

class GhostBoltSpeedPreview : public HackablePreview
{
public:
	static GhostBoltSpeedPreview* create();

	HackablePreview* clone() override;

protected:
	GhostBoltSpeedPreview();
	virtual ~GhostBoltSpeedPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* ghostbolt = nullptr;
	LocalizedLabel* xmm1Left = nullptr;
	LocalizedLabel* xmm1Right = nullptr;
};
