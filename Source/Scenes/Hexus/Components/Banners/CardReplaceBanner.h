#pragma once

#include "Scenes/Hexus/Components/Banners/BannerBase.h"

namespace cocos2d
{
	class ParticleSystemQuad;
	class Sprite;
}

class CardReplaceBanner : public BannerBase
{
public:
	static CardReplaceBanner* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

	cocos2d::Sprite* penaltyIcon;
	cocos2d::ParticleSystemQuad* penaltyIconParticles;

private:
	typedef BannerBase super;

	CardReplaceBanner();
	~CardReplaceBanner();

	void onEnter() override;
	void initializePositions() override;
};
