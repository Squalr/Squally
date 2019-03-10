#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class CatapultGenericPreview : public HackablePreview
{
public:
	static CatapultGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	CatapultGenericPreview();
	virtual ~CatapultGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewAsteroid;
};
