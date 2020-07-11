#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class MineCartPreview : public HackablePreview
{
public:
	static MineCartPreview* create();

	HackablePreview* clone() override;

private:
	typedef HackablePreview super;

	MineCartPreview();
	virtual ~MineCartPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* previewCart;
};
