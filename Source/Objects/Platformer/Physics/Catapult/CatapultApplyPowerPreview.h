#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class CatapultApplyPowerPreview : public HackablePreview
{
public:
	static CatapultApplyPowerPreview* create();

	HackablePreview* clone() override;

protected:
	CatapultApplyPowerPreview();
	virtual ~CatapultApplyPowerPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;

	cocos2d::Sprite* catapultBall1;
	cocos2d::Sprite* catapultBall2;
	LocalizedLabel* xmm1Low;
	LocalizedLabel* xmm1High;
};
