#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

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

protected:
	FloatingAsteroidGetDensityPreview();
	virtual ~FloatingAsteroidGetDensityPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* previewAsteroid;
	LocalizedLabel* xmm0Top;
	LocalizedLabel* xmm0Bottom;
};
