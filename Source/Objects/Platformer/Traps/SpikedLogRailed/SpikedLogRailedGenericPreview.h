#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode;

class SpikedLogRailedGenericPreview : public HackablePreview
{
public:
	static SpikedLogRailedGenericPreview* create();

	HackablePreview* clone() override;

protected:
	SpikedLogRailedGenericPreview();
	virtual ~SpikedLogRailedGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* previewSpikedLogRailed = nullptr;
};
