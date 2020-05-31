#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LaserAnimation;

class ElectricityBeamGenericPreview : public HackablePreview
{
public:
	static ElectricityBeamGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ElectricityBeamGenericPreview();
	virtual ~ElectricityBeamGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	LaserAnimation* previewLaser;
};
