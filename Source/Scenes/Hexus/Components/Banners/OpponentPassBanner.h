#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class OpponentPassBanner : public BannerBase
{
public:
	static OpponentPassBanner* create();

protected:
	OpponentPassBanner();
	virtual ~OpponentPassBanner();

	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef BannerBase super;

	cocos2d::Sprite* opponentPassBanner1;
	cocos2d::Sprite* opponentPassBanner2;
};
