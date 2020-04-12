#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class SmartAnimationSequenceNode;

class SpikeLogSetRotationPreview : public HackablePreview
{
public:
	static SpikeLogSetRotationPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	SpikeLogSetRotationPreview();
	virtual ~SpikeLogSetRotationPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* previewSpikedLog;
	LocalizedLabel* ecxAnimationCount;
	ConstantString* countString;
};
