#pragma once
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class PlayerFirstBanner : public BannerBase
{
public:
	static PlayerFirstBanner* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef BannerBase super;
	PlayerFirstBanner();
	~PlayerFirstBanner();

	void initializePositions() override;

	cocos2d::Sprite* playerBanner1;
	cocos2d::Sprite* playerBanner2;
};
