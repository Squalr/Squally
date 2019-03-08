#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class FloatingAsteroidGetDensityPreview : public HackablePreview
{
public:
	static FloatingAsteroidGetDensityPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	FloatingAsteroidGetDensityPreview();
	virtual ~FloatingAsteroidGetDensityPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewAsteroid;
	LocalizedLabel* xmm0Top;
	LocalizedLabel* xmm0Bottom;
};
