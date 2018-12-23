#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class OpponentPassBanner : public BannerBase
{
public:
	static OpponentPassBanner* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	OpponentPassBanner();
	~OpponentPassBanner();

	void initializePositions() override;

	cocos2d::Sprite* opponentPassBanner1;
	cocos2d::Sprite* opponentPassBanner2;
};
