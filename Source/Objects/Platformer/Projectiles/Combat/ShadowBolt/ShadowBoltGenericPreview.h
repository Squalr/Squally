#pragma once

#include "Engine/Hackables/HackablePreview.h"

class SmartAnimationSequenceNode;

class ShadowBoltGenericPreview : public HackablePreview
{
public:
	static ShadowBoltGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ShadowBoltGenericPreview();
	virtual ~ShadowBoltGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* shadowBolt;
};
