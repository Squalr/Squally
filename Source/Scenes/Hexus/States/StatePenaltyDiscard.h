#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StatePenaltyDiscard : public StateBase
{
public:
	static StatePenaltyDiscard * create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StatePenaltyDiscard();
	~StatePenaltyDiscard();

	void initializePositions() override;
	void initializeCallbacks(GameState* gameState);
	void discardCard(Card* cardToDiscard, GameState* gameState);

	Sprite* penaltyIcon;
	ParticleSystemQuad* penaltyIconParticles;
};
