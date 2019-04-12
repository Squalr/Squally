#pragma once
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class PlayerTurnBanner : public BannerBase
{
public:
	static PlayerTurnBanner* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef BannerBase super;
	PlayerTurnBanner();
	~PlayerTurnBanner();

	void initializePositions() override;

	cocos2d::Sprite* playerBanner1;
	cocos2d::Sprite* playerBanner2;
};
