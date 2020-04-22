#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class FloatingCrateGenericPreview : public HackablePreview
{
public:
	static FloatingCrateGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	FloatingCrateGenericPreview();
	virtual ~FloatingCrateGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewAsteroid;
};
