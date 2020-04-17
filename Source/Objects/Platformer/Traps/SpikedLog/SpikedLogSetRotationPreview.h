#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class SmartAnimationSequenceNode;

class SpikedLogSetRotationPreview : public HackablePreview
{
public:
	static SpikedLogSetRotationPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	SpikedLogSetRotationPreview();
	virtual ~SpikedLogSetRotationPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* previewSpikedLog;
	LocalizedLabel* ecxAnimationCount;
	ConstantString* countString;
};
