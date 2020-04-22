#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode;

class MetalSpikesGenericPreview : public HackablePreview
{
public:
	static MetalSpikesGenericPreview* create();

	HackablePreview* clone() override;

protected:
	MetalSpikesGenericPreview();
	virtual ~MetalSpikesGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* previewSpikes;
};
