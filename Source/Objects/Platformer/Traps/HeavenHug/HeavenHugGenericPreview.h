#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class HeavenHugGenericPreview : public HackablePreview
{
public:
	static HeavenHugGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	HeavenHugGenericPreview();
	virtual ~HeavenHugGenericPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewHeavenHug;
};
