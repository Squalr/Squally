#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LaserAnimation;
class LocalizedLabel;
class SmartAnimationSequenceNode;

class ElectricityBeamCountDownPreview : public HackablePreview
{
public:
	static ElectricityBeamCountDownPreview* create();

	HackablePreview* clone() override;

protected:
	ElectricityBeamCountDownPreview();
	virtual ~ElectricityBeamCountDownPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	LaserAnimation* previewLaser;
};
