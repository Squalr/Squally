#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class FloatingAsteroidGenericPreview : public HackablePreview
{
public:
	static FloatingAsteroidGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	FloatingAsteroidGenericPreview();
	virtual ~FloatingAsteroidGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewAsteroid;
};
