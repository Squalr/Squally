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

	SmartAnimationSequenceNode* previewSpikedLogRailed = nullptr;
	cocos2d::Sprite* previewSqually = nullptr;
	LocalizedLabel* eaxLabel = nullptr;
	ConstantString* eaxString = nullptr;
	int currentAnimationIndex = -1;
	int animationLength = 0;
};
