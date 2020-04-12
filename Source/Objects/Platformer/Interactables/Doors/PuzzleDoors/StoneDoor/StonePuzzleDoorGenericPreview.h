#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode;

class StonePuzzleDoorGenericPreview : public HackablePreview
{
public:
	static StonePuzzleDoorGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	StonePuzzleDoorGenericPreview();
	virtual ~StonePuzzleDoorGenericPreview();
	void onEnter() override;
	void initializePositions() override;
};
