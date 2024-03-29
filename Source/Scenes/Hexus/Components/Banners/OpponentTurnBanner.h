#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class OpponentTurnBanner : public BannerBase
{
public:
	static OpponentTurnBanner* create();

protected:
	OpponentTurnBanner();
	virtual ~OpponentTurnBanner();

	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef BannerBase super;

	cocos2d::Sprite* enemyBanner1 = nullptr;
	cocos2d::Sprite* enemyBanner2 = nullptr;
};
