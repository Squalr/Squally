#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode;

class GreenStonePuzzleDoorGenericPreview : public HackablePreview
{
public:
	static GreenStonePuzzleDoorGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	GreenStonePuzzleDoorGenericPreview();
	~GreenStonePuzzleDoorGenericPreview();
	void onEnter() override;
	void initializePositions() override;
};
