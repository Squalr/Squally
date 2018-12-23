#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class OpponentRoundWinBanner : public BannerBase
{
public:
	static OpponentRoundWinBanner* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	OpponentRoundWinBanner();
	~OpponentRoundWinBanner();

	void initializePositions() override;

	Sprite* playerPassBanner1;
	Sprite* playerPassBanner2;
};
