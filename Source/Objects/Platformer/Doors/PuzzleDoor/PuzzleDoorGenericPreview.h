#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode;

class PuzzleDoorGenericPreview : public HackablePreview
{
public:
	static PuzzleDoorGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	PuzzleDoorGenericPreview();
	virtual ~PuzzleDoorGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* previewSpikedLog;
};
