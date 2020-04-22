#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode;

class WoodenSpikesGenericPreview : public HackablePreview
{
public:
	static WoodenSpikesGenericPreview* create();

	HackablePreview* clone() override;

protected:
	WoodenSpikesGenericPreview();
	virtual ~WoodenSpikesGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* previewSpikes;
};
