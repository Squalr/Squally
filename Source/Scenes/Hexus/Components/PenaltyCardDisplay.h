#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class PenaltyCardDisplay : public ComponentBase
{
public:
	static PenaltyCardDisplay * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onStateChange(GameState* eventCustom) override;

private:
	PenaltyCardDisplay();
	~PenaltyCardDisplay();

	void onEnter() override;
	void initializePositions() override;

	Sprite* penaltyCardSprite;
	Label* penaltyCardLabel;
	ParticleSystemQuad* penaltyParticles;

	Sprite* enemyPenaltyCardSprite;
	Label* enemyPenaltyCardLabel;
	ParticleSystemQuad* enemyPenaltyParticles;
};
