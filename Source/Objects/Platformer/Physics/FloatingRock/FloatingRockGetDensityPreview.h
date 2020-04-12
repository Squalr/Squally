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

private:
	typedef HackablePreview super;

	FloatingRockGetDensityPreview();
	virtual ~FloatingRockGetDensityPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewAsteroid;
	LocalizedLabel* xmm0Top;
	LocalizedLabel* xmm0Bottom;
};
