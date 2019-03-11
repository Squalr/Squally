#pragma once

#include "Engine/Hackables/HackablePreview.h"

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

private:
	typedef HackablePreview super;

	CatapultApplyPowerPreview();
	virtual ~CatapultApplyPowerPreview() = default;
	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* catapultBall1;
	cocos2d::Sprite* catapultBall2;
	LocalizedLabel* xmm1Low;
	LocalizedLabel* xmm1High;
};
