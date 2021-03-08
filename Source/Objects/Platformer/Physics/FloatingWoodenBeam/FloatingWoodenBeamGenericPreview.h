#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class FloatingWoodenBeamGenericPreview : public HackablePreview
{
public:
	static FloatingWoodenBeamGenericPreview* create();

	HackablePreview* clone() override;

protected:
	FloatingWoodenBeamGenericPreview();
	virtual ~FloatingWoodenBeamGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* previewAsteroid;
};
