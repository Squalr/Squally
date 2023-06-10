#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode;

class LavaFlowGenericPreview : public HackablePreview
{
public:
	static LavaFlowGenericPreview* create();

	HackablePreview* clone() override;

protected:
	LavaFlowGenericPreview();
	virtual ~LavaFlowGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* ripple = nullptr;
};
