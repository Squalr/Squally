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
	RoundBanner();
	virtual ~RoundBanner();

	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef BannerBase super;

	cocos2d::Sprite* roundBanner1;
	cocos2d::Sprite* roundBanner2;
};
