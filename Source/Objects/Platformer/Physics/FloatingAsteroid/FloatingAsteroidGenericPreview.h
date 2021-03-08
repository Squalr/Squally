#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class FloatingAsteroidGenericPreview : public HackablePreview
{
public:
	static FloatingAsteroidGenericPreview* create();

	HackablePreview* clone() override;

protected:
	FloatingAsteroidGenericPreview();
	virtual ~FloatingAsteroidGenericPreview();

private:
	typedef HackablePreview super;

	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewAsteroid;
};
