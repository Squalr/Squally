#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

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

protected:
	LaserCountDownPreview();
	virtual ~LaserCountDownPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	LaserAnimation* previewLaser;
};
