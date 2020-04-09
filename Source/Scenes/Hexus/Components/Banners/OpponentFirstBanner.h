#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class OpponentFirstBanner : public BannerBase
{
public:
	static OpponentFirstBanner* create();

protected:
	OpponentFirstBanner();
	virtual ~OpponentFirstBanner();

	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef BannerBase super;

	cocos2d::Sprite* enemyBanner1;
	cocos2d::Sprite* enemyBanner2;
};
