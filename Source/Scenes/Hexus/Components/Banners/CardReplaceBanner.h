#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class Sprite;
}

class SmartParticles;

class CardReplaceBanner : public BannerBase
{
public:
	static CardReplaceBanner* create();

protected:
	CardReplaceBanner();
	virtual ~CardReplaceBanner();

	void onEnter() override;
	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

	cocos2d::Sprite* penaltyIcon;
	SmartParticles* penaltyIconParticles;

private:
	typedef BannerBase super;
};
