#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class FloatingRockGenericPreview : public HackablePreview
{
public:
	static FloatingRockGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	FloatingRockGenericPreview();
	virtual ~FloatingRockGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewAsteroid;
};
