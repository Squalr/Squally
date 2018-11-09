#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class RemainingCardDisplay : public ComponentBase
{
public:
	static RemainingCardDisplay * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	RemainingCardDisplay();
	~RemainingCardDisplay();

	void initializePositions() override;
	void onRemaningCardDisplayMouseOver();
	void onRemaningCardDisplayMouseOut();
	void enableCardDisplayInteraction();
	void disableCardDisplayInteraction();

	ParticleSystemQuad* particles;

	MenuSprite* remainingCardSprite;
	Label* remainingCardLabel;

	LayerColor* remainingCardMouseOverPanel;
	Label* remainingCardMouseOverLabel;

	Sprite* enemyRemainingCardSprite;
	Label* enemyRemainingCardLabel;
};
