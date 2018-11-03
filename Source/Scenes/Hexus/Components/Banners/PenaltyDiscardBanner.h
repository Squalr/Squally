#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/Banners/BannerBase.h"

using namespace cocos2d;

class PenaltyDiscardBanner : public BannerBase
{
public:
	static PenaltyDiscardBanner * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onStateChange(GameState* eventCustom) override;

private:
	PenaltyDiscardBanner();
	~PenaltyDiscardBanner();

	void initializePositions() override;

	Sprite* penaltyIcon;
	ParticleSystemQuad* penaltyIconParticles;
};
