#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class SmartAnimationSequenceNode;

class MulDoorPreview : public HackablePreview
{
public:
	static MulDoorPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	MulDoorPreview();
	~MulDoorPreview();
	void onEnter() override;
	void initializePositions() override;
};
