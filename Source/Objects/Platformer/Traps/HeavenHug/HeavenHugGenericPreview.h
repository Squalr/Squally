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
	~HeavenHugGenericPreview() = default;
	void onEnter() override;

	cocos2d::Sprite* previewBlade;
};
