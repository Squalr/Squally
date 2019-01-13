#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class SmartAnimationSequenceNode;

class SpikeLogSetRotation : public HackablePreview
{
public:
	static SpikeLogSetRotation* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	SpikeLogSetRotation();
	~SpikeLogSetRotation() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* previewSpikedLog;
	LocalizedLabel* ecxAnimationCount;
	ConstantString* countString;
};
