#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class ConstantString;
class LocalizedLabel;
class SmartAnimationSequenceNode;

class SpikedLogRailedSetRotationPreview : public HackablePreview
{
public:
	static SpikedLogRailedSetRotationPreview* create();

	HackablePreview* clone() override;

protected:
	SpikedLogRailedSetRotationPreview();
	virtual ~SpikedLogRailedSetRotationPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	void onFrameComplete();

	SmartAnimationSequenceNode* previewSpikedLogRailed = nullptr;
	LocalizedLabel* ecxAnimationCount = nullptr;
	ConstantString* countString = nullptr;
	int currentAnimationIndex = -1;
	int animationLength = 0;
};
