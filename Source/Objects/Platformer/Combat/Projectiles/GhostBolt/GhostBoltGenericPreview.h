#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class SmartAnimationSequenceNode;

class GhostBoltGenericPreview : public HackablePreview
{
public:
	static GhostBoltGenericPreview* create();

	HackablePreview* clone() override;

protected:
	GhostBoltGenericPreview();
	virtual ~GhostBoltGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* ghostbolt = nullptr;
};
