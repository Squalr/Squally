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

protected:
	FloatingCrateGetDensityPreview();
	virtual ~FloatingCrateGetDensityPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* previewAsteroid;
	LocalizedLabel* xmm0Top;
	LocalizedLabel* xmm0Bottom;
};
