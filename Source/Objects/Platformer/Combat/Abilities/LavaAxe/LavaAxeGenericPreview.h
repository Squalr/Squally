#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
};

class LavaAxeGenericPreview : public HackablePreview
{
public:
	static LavaAxeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	LavaAxeGenericPreview();
	virtual ~LavaAxeGenericPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* axe = nullptr;
};
