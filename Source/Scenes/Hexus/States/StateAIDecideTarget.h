#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Engine/Sound/SoundManager.h"
#include "Resources.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StateAIDecideTarget : public StateBase
{
public:
	static StateAIDecideTarget * create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateAIDecideTarget();
	~StateAIDecideTarget();
};
