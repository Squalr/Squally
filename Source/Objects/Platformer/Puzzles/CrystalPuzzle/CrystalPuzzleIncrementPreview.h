#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class SmartAnimationSequenceNode;

class CrystalPuzzleIncrementPreview : public HackablePreview
{
public:
	static CrystalPuzzleIncrementPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	CrystalPuzzleIncrementPreview();
	virtual ~CrystalPuzzleIncrementPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* previewSpikedLog;
	LocalizedLabel* ecxAnimationCount;
	ConstantString* countString;
};
