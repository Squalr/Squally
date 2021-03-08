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

protected:
	FloatingCrateGenericPreview();
	virtual ~FloatingCrateGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* previewAsteroid;
};
