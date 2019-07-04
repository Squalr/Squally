#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode;

class CrystalPuzzleGenericPreview : public HackablePreview
{
public:
	static CrystalPuzzleGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	CrystalPuzzleGenericPreview();
	virtual ~CrystalPuzzleGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* previewSpikedLog;
};
