#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class IcicleGetDensityPreview : public HackablePreview
{
public:
	static IcicleGetDensityPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	IcicleGetDensityPreview();
	virtual ~IcicleGetDensityPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewAsteroid;
	LocalizedLabel* xmm0Top;
	LocalizedLabel* xmm0Bottom;
};
