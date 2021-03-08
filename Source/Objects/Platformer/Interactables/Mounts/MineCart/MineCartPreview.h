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

protected:
	MineCartPreview();
	virtual ~MineCartPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* previewCart;
};
