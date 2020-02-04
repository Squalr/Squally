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
	VictoryBanner();
	virtual ~VictoryBanner();

	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef BannerBase super;

	cocos2d::Sprite* victoryBanner1;
	cocos2d::Sprite* victoryBanner2;
};
