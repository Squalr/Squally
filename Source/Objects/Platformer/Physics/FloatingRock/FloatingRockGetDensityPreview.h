#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class FloatingRockGetDensityPreview : public HackablePreview
{
public:
	static FloatingRockGetDensityPreview* create();

	HackablePreview* clone() override;

protected:
	FloatingRockGetDensityPreview();
	virtual ~FloatingRockGetDensityPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* previewAsteroid;
	LocalizedLabel* xmm0Top;
	LocalizedLabel* xmm0Bottom;
};
