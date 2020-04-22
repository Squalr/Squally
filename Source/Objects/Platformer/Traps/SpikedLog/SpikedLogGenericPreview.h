#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode;

class SpikedLogGenericPreview : public HackablePreview
{
public:
	static SpikedLogGenericPreview* create();

	HackablePreview* clone() override;

protected:
	SpikedLogGenericPreview();
	virtual ~SpikedLogGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	SmartAnimationSequenceNode* previewSpikedLog;
};
