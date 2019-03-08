#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class FloatingWoodenBeamGenericPreview : public HackablePreview
{
public:
	static FloatingWoodenBeamGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	FloatingWoodenBeamGenericPreview();
	virtual ~FloatingWoodenBeamGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewAsteroid;
};
