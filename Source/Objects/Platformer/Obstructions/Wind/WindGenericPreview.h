#pragma once

#include "Engine/Hackables/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class WindGenericPreview : public HackablePreview
{
public:
	static WindGenericPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	WindGenericPreview();
	~WindGenericPreview() = default;
	void onEnter() override;

	cocos2d::Sprite* previewHeavenHug;
};
