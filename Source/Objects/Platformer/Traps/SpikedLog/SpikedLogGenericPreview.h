#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode;

class SpikedLogGenericPreview : public HackablePreview
{
public:
	static SpikedLogGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	SpikedLogGenericPreview();
	virtual ~SpikedLogGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* previewSpikedLog;
};
