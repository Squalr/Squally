#pragma once
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class VictoryBanner : public BannerBase
{
public:
	static VictoryBanner * create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef BannerBase super;
	VictoryBanner();
	~VictoryBanner();

	void initializePositions() override;

	cocos2d::Sprite* victoryBanner1;
	cocos2d::Sprite* victoryBanner2;
};
