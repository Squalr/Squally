#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"

#include "ComponentBase.h"

using namespace cocos2d;

class ControlNeutral : public ComponentBase
{
public:
	static ControlNeutral * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	ControlNeutral();
	~ControlNeutral();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void initializeCallbacks(GameState* gameState);
	void aiDoSelection(GameState* gameState);
	void selectCard(Card* card);

	GameState* activeGameState;
};
