#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LaserAnimation;
class LocalizedLabel;
class SmartAnimationSequenceNode;

class LaserCountDownPreview : public HackablePreview
{
public:
	static LaserCountDownPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	LaserCountDownPreview();
	virtual ~LaserCountDownPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	LaserAnimation* previewLaser;
};
