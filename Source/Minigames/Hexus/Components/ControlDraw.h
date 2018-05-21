#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexus/Components/ComponentBase.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class ControlDraw : public ComponentBase
{
public:
	static ControlDraw * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	ControlDraw();
	~ControlDraw();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void doInitialCardDraw(GameState* gameState);
	void doCardDraw(GameState* gameState);
};
