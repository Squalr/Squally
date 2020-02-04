#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class DrawBanner : public BannerBase
{
public:
	static DrawBanner* create();

protected:
	DrawBanner();
	virtual ~DrawBanner();

	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef BannerBase super;

	cocos2d::Sprite* defeatBanner1;
	cocos2d::Sprite* defeatBanner2;
};
