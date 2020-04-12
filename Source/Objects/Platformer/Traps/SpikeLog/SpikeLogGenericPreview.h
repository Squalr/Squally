#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

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
	virtual ~SpikeLogGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* previewSpikedLog;
};
