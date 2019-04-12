#pragma once
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class RoundBanner : public BannerBase
{
public:
	static RoundBanner* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef BannerBase super;
	RoundBanner();
	~RoundBanner();

	void initializePositions() override;

	cocos2d::Sprite* roundBanner1;
	cocos2d::Sprite* roundBanner2;
};
