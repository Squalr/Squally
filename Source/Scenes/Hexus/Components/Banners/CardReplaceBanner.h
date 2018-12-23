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
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

	cocos2d::Sprite* penaltyIcon;
	cocos2d::ParticleSystemQuad* penaltyIconParticles;

private:
	CardReplaceBanner();
	~CardReplaceBanner();

	void onEnter() override;
	void initializePositions() override;
};
