#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class FloatingCrateGetDensityPreview : public HackablePreview
{
public:
	static FloatingCrateGetDensityPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	FloatingCrateGetDensityPreview();
	virtual ~FloatingCrateGetDensityPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewAsteroid;
	LocalizedLabel* xmm0Top;
	LocalizedLabel* xmm0Bottom;
};
