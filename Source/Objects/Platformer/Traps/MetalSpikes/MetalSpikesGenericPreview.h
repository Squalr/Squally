#pragma once

#include "Engine/Hackables/HackablePreview.h"

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

private:
	typedef HackablePreview super;

	MetalSpikesGenericPreview();
	~MetalSpikesGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* previewSpikes;
};
