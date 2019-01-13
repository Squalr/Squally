#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode;

class SpikeLogGenericPreview : public HackablePreview
{
public:
	static SpikeLogGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	SpikeLogGenericPreview();
	~SpikeLogGenericPreview() = default;
	void onEnter() override;

	SmartAnimationSequenceNode* previewSpikedLog;
};
