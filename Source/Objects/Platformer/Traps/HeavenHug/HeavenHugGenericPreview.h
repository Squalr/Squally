#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class HeavenHugGenericPreview : public HackablePreview
{
public:
	static HeavenHugGenericPreview* create();

	HackablePreview* clone() override;

protected:
	HeavenHugGenericPreview();
	virtual ~HeavenHugGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* previewHeavenHug;
};
