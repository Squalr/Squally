#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode;

class GatePuzzleDoorGenericPreview : public HackablePreview
{
public:
	static GatePuzzleDoorGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	GatePuzzleDoorGenericPreview();
	~GatePuzzleDoorGenericPreview();
	void onEnter() override;
	void initializePositions() override;
};
