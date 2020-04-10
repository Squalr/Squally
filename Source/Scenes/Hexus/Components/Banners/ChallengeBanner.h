#pragma once
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class ChallengeBanner : public BannerBase
{
public:
	static ChallengeBanner* create();

protected:
	ChallengeBanner();
	virtual ~ChallengeBanner();

	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef BannerBase super;

	cocos2d::Sprite* roundBanner1;
	cocos2d::Sprite* roundBanner2;
};
