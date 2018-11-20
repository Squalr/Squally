#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class TutorialBase : public ComponentBase
{
protected:
	TutorialBase();
	~TutorialBase();

	void onEnter() override;
	void onAnyRequestStateChange(GameState* gameState) override;
	virtual bool tryHijackState(GameState* gameState) = 0;

	bool tutorialShown;
};
